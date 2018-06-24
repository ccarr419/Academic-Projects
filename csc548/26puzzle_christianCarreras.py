#   ORIGINAL AUTHOR IS UNKNOWN, THIS IS NOT MY CODE
#   ALL CODE WAS PROVIDED BY MY PROFESSOR FOR A PROJECT
#
#   Modifications By: Christian Carreras
#   File Name: 26puzzle_christianCarreras.py
#   Date: 02/22/2017
#   Course Name: Artificial Intelligence II
#   Course Number: CSC 548
#   Professor: Dr. Rieksts
#   Term: SPRING 2017
#   Institution: Kutztown University
#   Project: #1
#   Due Date: 02/27/2017
#   About: This program finds the shortest path between two
#       configurations of a modified 8-puzzle. The modifications
#       are simply adding an extra dimension to the 8-puzzle thus
#       making it a 26-puzzle. To find the shortest path,
#       data structures such as lists, dictionaries, nodes,
#       multi-dimensional arrays, etc. are used. The Manhattan
#       Distance heuristic is used to solve this problem as well.

from copy import copy
from copy import deepcopy
import bisect

# The main function
# Finds the shortest path from icfg to gcfg
# icfg = initial configuration, which is the initial state
# gcfg = goal configuration, which is the goal state
# Each configurations (state) when it is encountered is given 
#     and identification number (Id)
# The function uses 3 lists in parallel = WL< WLfs, WLids
# WL = waiting list of nodes to be expanded
# WLfs = list of f-values, in parallel with WL
# WLids = list of Ids, in parallel with WL
# goalId = the Id of the goal state
# iNode = the node for the initial state
# curNode = the node currently being processed

def findPath(icfg,gcfg):
        print ('icfg',icfg)
# Initialize WL< WLfs, WLids
        WL=[]
        WLfs=[]
        WLids=[]
# generate the Id of the goal configuration (state)
        goalId=genCfId(gcfg)
# Call makNd to create a node for the initial state
        iNode = makNd(genCfId(icfg),icfg,0,manh(icfg,gcfg),[])
        curNode=iNode
# Loop until the current node, the one taken from the head of WL,
#     has an Id matching the goal Id
        while curNode['cfid'] != goalId:
# Expand current node, returning a list of "newNodes"
                newNodes=xpdNd(curNode,gcfg)
# Apply filtering process keeping only the "good" nodes of newNodes
                WL,WLfs,WLids=adGoods(newNodes,WL,WLfs,WLids)
# Grab the node at the head of WL, making it the current node
                curNode=WL[0]
# Remove it from WL; also remove corresponding values from WLfs, WLids
                WL.remove(curNode)
                WLfs.remove(WLfs[0])
                WLids.remove(WLids[0])
# Return the path to reach the current node
        return curNode['path']

# Function to apply filtering process retaining only the "good nodes"
# Add these "good" nodes to WL, WLfs, WLids
# Filtering function is keepIfBetter
# nwNds = list of newly created nodes
# wl, wlfs, wlids = current value of WL, WLfs, WLids
def adGoods(nwNds,wl,wlfs,wlids):
        for nd in nwNds:
# If we have seen this node before (node's cfid is in waiting list of Ids)
#      keep only if it is "better" than the one already seen
#      if not, nd becomes null
                if nd['cfid'] in wlids:
                        nd=keepIfBetter(nd,wl,wlids)
# If nd was kept (did not become null)
#     insert it into WL, WLfs, WLids
                if nd:
                        wl,wlfs,wlids=insertKeyed(nd,nd['f'],wl,wlfs,wlids)
# Return updated values of WL< WLfs, WLids
        return wl,wlfs,wlids

# The filtering function which is called if the state has been seen before
# nd = the node being checked
# wl, wlids = current value of WL, Wlids
def keepIfBetter(nd,wl,wlids):
# Get the index of whcre the Id of this node is found in wlids
        indx=wlids.index(nd['cfid'])
# From WL get the corresponding node
        oldNode=wl[indx]
# If g-value of nd is < that of the "old" node - keep it
        if nd['g']<oldNode['g']:
                return nd
# Otherwise return the empty list
        else:
                return []

# Generate the Id of a configuration (state)
# cfg = a puzzle configuration (state)
# cfid = the calculated Id of this state
# Note to reader - run this function of a few states and it will be
#     immediately clear how this function works
def genCfId(cfg):
        cfid = 0
        for lvl in  range(3):
            for row in range(3):
                for col in range(3):
                        cfid = cfid*10+cfg[lvl][row][col]
        return cfid

# Function to find in which row and column item is found
# item = value being sought in a 3D array
# ray3d = a 3 dimensional array
# Because the function is generic, it uses range of the number of levels,
#   rows, and columns to stay within bounds
def rcOf(item,ray3d):
	return [(l,r,c) for l in range(len(ray3d)) for r in range(len(ray3d)) for c in range(len(ray3d[0])) if ray3d[l][r][c]==item][0]

# Function to compute the Manhattan distance
# cfg1 = a configuration (state)
# cfg2 = a second configuration (state)
# m = variable holding the value to be returned
# l1, r1, c1 = the level, row, column of a particular value of cfg1
# l2, r2, c2 = the level, row, column of a particular value of cfg2
def manh(cfg1,cfg2):
        m=0
# The values in each configuration run from 1 to 26
# For each such value, we find its level, row, and column
        for i in range(1,27):
                l1,r1,c1=rcOf(i,cfg1)
                l2,r2,c2=rcOf(i,cfg2)
# For the values 1 to 26
#    add to m the distance that must be travaled to match cfg1 to cg=fg2
                m+=abs(l1-l2)+abs(r1-r2)+abs(c1-c2)
        return m

# Generate all possible moves from this state (configuration)
# cfg = a particular configuration of the puzzle
# mvLsL = the list of possible moves from each position in a level
# mvLsR = the list of possible moves from each position in a row
# mvLsC = the list of possible moves from each position in a column
# le, re, ce = the level, row, column of the empty space (represented by 0)
def genMvs(cfg):
        mvLsL=[['up'],['down','up'],['down']]
        mvLsR=[['north'],['north','south'],['south']]
        mvLsC=[['west'],['east','west'],['east']]       
# Get the level, row, column of the empty space (0)
        le,re,ce=rcOf(0,cfg)
# Based on the level,row,column value, get the list of moves
#    from mvLsL,mvLsr, mvLsC
        return mvLsL[le]+mvLsR[re]+mvLsC[ce]

# Function to make a new configuration
# mv = the move to take, resulting in a new state (configuration)
# cfg = the current state (configuration)
# le,re,ce = level,row,column of the empty space
# lf,rf,cf = level,row,column of the tile to be moved
# lmv,rmv,cmv = the amount (1,-1) tile must be moved 
#     from level to level, row to row, from column to column
# newCfg = the configuration resulting from that move
# findLoc = a dictionary used for lookup
#    it gives the amount (1,-1) that a tile has to be moved
#    in order to go to its new location
def mkNwCfg(mv,cfg):
# Get the level, row, column of the empty space
        le,re,ce=rcOf(0,cfg)
        findLoc={'up':(1,0,0),'down':(-1,0,0),'north':(0,1,0),'south':(0,-1,0),'east':(0,0,-1),'west':(0,0,1)}
# Use findLoc to calculate the amount by which tile must be moved
        lmv,rmv,cmv=findLoc[mv]
# Calculate the new level, row, column of tile being moved
        lf,rf,cf=(le+lmv,re+rmv,ce+cmv)
# Before making the move, make a "deep" copy of configuration
        newCfg=deepcopy(cfg)
# Place the tile being moved, which is at position lf,rf,cf,
#    into the empty space, which is at re,ce
        newCfg[le][re][ce]=newCfg[lf][rf][cf]
# Replace the old position of the tile, lf,rf,cf, by 0
        newCfg[lf][rf][cf]=0
        return newCfg

# Function to make the node resulting from a tile being moved
# mv = the move that is to be made
# node = the current node whose tile is being moved
# gcfg = the goal state (configuration)
# newCfg = the new configuration resulting from the tile being moved
# g = the g-value of the current node
# h = the heuristic value calculated by the funciton "manh"
# nwNdpath = the path from initial state to this new state
def makMvNd(mv,node,gcfg):
# Call mkNwCfg to get the state resulting from this move
        nwCfg=mkNwCfg(mv,node['cfg'])
        g=node['g']
        h=manh(nwCfg,gcfg)
# Make a copy of the path to the node from which move is being made
#   and append to the path the move being made
        nwNdpath=copy(node['path'])
        nwNdpath.append(mv)
# Build the dictionary of the new node
#   notice the calculation of the new g-value and the new f-value
        return {'cfid':genCfId(nwCfg),'cfg':nwCfg,'g':g+1,'h':h,'f':g+1+h,'path':nwNdpath}

# Build the dictionary of a node, given all of its component values
# cfid,cfg,g,h,path - the component values of the node to be made
def makNd(cfid,cfg,g,h,path):
        return {'cfid':cfid,'cfg':cfg,'g':g,'h':h,'f':g+h,'path':path}

# Function to expand a node by finding its neighbors
#   and calculating the resulting new nodes
# Calls genMvs to generate all possible moves
#    and makMvNd to make the nodes resulting from these moves
# Uses a map and lambda combination which will be explained in class
# node = node to be expanded
# gcfg = goal state (configuration) - needed for calculating heuristic value
def xpdNd(node,gcfg):
        return map(lambda mv:makMvNd(mv,node,gcfg),genMvs(node['cfg']))

#Utilities
# separate a list of ordered pairs into two lists - the 1sts and the 2nds
# pairs = the pairs to be separated
def sepL(pairs):
	return map(lambda x:x[0],pairs),map(lambda x:x[1],pairs)

#Insert item into an already sorted list by key value
# Uses bisect to split the sorted lists at the place of insertion
#    and the slice operation to separate the lists into two parts
# node = the node to be inserted into the list
# f = the f-value, by which the list is ordered
# L = the list into which insertion is to be made
#    correspons to WL, as seen above
# keysL = list of keys of L
#    corresonds to WLfs, as seen above
# idsL = list of configuration Ids
#    corresponds to WLids, as seen above
# place = the place where node is to be inserted into L
# Returns what will become the new values of WL, WLfs, WLids
def insertKeyed(node,f,L,keysL,idsL):
	place=bisect.bisect_left(keysL,f)
	return L[:place]+[node]+L[place:],keysL[:place]+[f]+keysL[place:],idsL[:place]+[node['cfid']]+idsL[place:]

# Test data
# gcfg = goal state (configuration)
gcfg = [[[1,2,3],[4,5,6],[7,8,9]],[[10,11,12],[13,14,15],[16,17,18]],[[19,20,21],[22,23,24],[25,26,0]]]

# hcfg = testing one level up
hcfg = [[[1,2,3],[4,5,6],[7,8,9]],[[10,11,12],[13,14,15],[16,17,0]],[[19,20,21],[22,23,24],[25,26,18]]]

# ocfg = starting the empty space in the middle of the puzzle (simple 3d solving)
ocfg = [[[1,2,3],[4,5,6],[7,8,9]],[[10,11,12],[13,0,15],[16,14,17]],[[19,20,21],[22,23,24],[25,26,18]]]

# scfg = starting the empty space in the first level (simple 3d solving)
scfg = [[[1,2,3],[4,5,6],[7,8,0]],[[10,11,12],[13,14,15],[16,17,9]],[[19,20,21],[22,23,24],[25,26,18]]]

# scfg2 = starting the empty space in the first level (simple 3d solving)
scfg2 = [[[1,2,3],[4,5,6],[7,8,0]],[[10,11,12],[13,14,18],[16,17,9]],[[19,20,21],[22,23,15],[25,26,24]]]

# test = testing with only 2-dimensions in a 3D puzzle
test = [[[1,2,3],[4,5,6],[7,8,9]],[[10,11,12],[13,14,15],[16,17,18]],[[22,19,23],[25,21,20],[26,0,24]]]

# test2 = moderate 3d solving
test2 = [[[2,5,3],[4,0,6],[7,8,9]],[[1,10,12],[13,11,14],[16,17,18]],[[19,20,21],[22,23,15],[25,26,24]]]

# test3 = moderate 3d solving
test3 = [[[10,5,2],[1,6,9],[8,4,18]],[[13,17,3],[25,0,14],[7,16,15]],[[19,11,12],[23,20,21],[22,26,24]]]


nwcfg = [[[0,1,2],[3,4,5],[6,7,8]],[[9,10,11],[12,13,14],[15,16,17]],[[18,19,20],[21,22,23],[24,25,26]]]