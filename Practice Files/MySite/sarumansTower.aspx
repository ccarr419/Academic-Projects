<%@ Page Title ="Saruman's Tower" Language="C#" MasterPageFile="~/MasterPage/MasterPage.master" AutoEventWireup="true" CodeFile="sarumansTower.aspx.cs" Inherits="sarumansTower" %>

<asp:Content ID="headContent" ContentPlaceHolderID="head" runat="server">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js"></script>
    <script>
        $(document).ready(function () {
            $("#tvScreen").css("background-image", "url(Images/duckHunt.gif");
            $("#tvScreen").css("background-size", "100%", "100%");
            $("#tvScreen").css("background-position", "center");
            $("#tvScreen").css("background-repeat", "no-repeat");
            $("#tvScreen").css("opacity", "0.7");
        });

        function getTowerLvl() {
            var day = $("#dayPicked").val();
            var lvl = findLevels(day);
            $("#towerLvl").val(lvl);
        }

        function findLevels(end_day) {
            if (end_day < 1) {
                $("#numOnes").val(0);
                return 0;
            }

            var day = 1, lvl = 0;
            while (day <= end_day) {
                num = popCnt(day);
                if (num != 0 && num % 3 == 0)
                    lvl++;
                day++;
            }

            $("#numOnes").val(num);
            return lvl;
        }

        function popCnt(n) {
            n >>>= 0 /* force uint32 */
            for (var popcnt = 0; n; n &= n - 1) {
                popcnt++
            }
            return popcnt
        }

    </script>
</asp:Content>
<asp:Content ID="mainPageContent" ContentPlaceHolderID="pageContent" runat="server">
    <table class =" centeredTable">
        <tr>
            <td colspan="2" class="paddedCell">
                Enter any number <i>n</i> where <i>n < 10<sup>7</sup></i>
            </td>
        </tr>
        <tr>
            <th class="rightAlignedHeaderCell">END DAY:</th>
            <td class="paddedCell"><input id="dayPicked" type="number" class="sarumanInput" required ="required" value="0" min="0" /></td>
        </tr>
        <tr>
            <th class="rightAlignedHeaderCell">ONE COUNT:</th>
            <td class="paddedCell"><input id="numOnes" type="text" class="sarumanInput" readonly="readonly" /></td>
        </tr>
        <tr>
            <th class="rightAlignedHeaderCell">TOWER LEVEL:</th>
            <td class="paddedCell"><input id="towerLvl" type="text" class="sarumanInput" readonly="readonly" /></td>
        </tr>
        <tr>
            <td colspan="2" class="paddedCell">
                <button class="smallButton1" onclick="getTowerLvl()">GET TOWER LEVEL</button>
            </td>
        </tr>
    </table>
</asp:Content>
