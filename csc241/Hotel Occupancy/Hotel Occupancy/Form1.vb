Public Class Form1
    ' This program finds the room occupancy for each for of a hotel
    ' and finds the occupancy rate for the floor and the whole hotel.
    ' Author: Christian Carreras

    Private Sub btnReport_Click(sender As System.Object, e As System.EventArgs) Handles btnReport.Click
        Dim intCounter As Integer = 1       ' Counter for the loop
        Dim intRoomOccupancy As Integer     ' Room occupancy for the floor
        Dim intTotalRooms As Integer        ' Total rooms occupied
        Dim dblOccupancyRate As Double      ' Occupancy rate of the floor
        Dim dblOverallOccupancy As Double   ' Averaged occupancy rate for hotel
        Dim strUserInput As String          ' User input from input box

        Do While intCounter <= 8
            ' Input box that recieves the user input of room occupancy for each floor.
            strUserInput = InputBox("Enter the the room occupancy for floor " & intCounter, "Room Occupancy")

            ' Check if the entered value is an integer.
            If Integer.TryParse(strUserInput, intRoomOccupancy) Then

                ' Check if the entered value is from 0-30.
                If intRoomOccupancy >= 0 And intRoomOccupancy <= 30 Then
                    dblOccupancyRate = intRoomOccupancy / 30

                    ' Add the floor, rooms occupied and occupancy rate to the list box.
                    lstOutput.Items.Add("Floor: " & intCounter & " Occupied: " & intRoomOccupancy &
                                        " Occupancy Rate: " & dblOccupancyRate.ToString("p"))

                    ' Add the occupancy rates together.
                    dblOverallOccupancy += dblOccupancyRate

                    ' Find the total number of rooms occupied.
                    intTotalRooms += intRoomOccupancy

                Else
                    ' If the user did not enter a value from 0-30.
                    MessageBox.Show("Enter an integer value from 0-30.")
                End If

            Else
                ' If the user did not enter an integer.
                MessageBox.Show("Enter an intger value from 0-30.")
            End If

            ' Increment intCounter.
            intCounter += 1

        Loop

        ' Average the overall occupany.
        dblOverallOccupancy /= 8

        ' Display the total rooms and overall room occupancy.
        lblTotalRooms.Text = intTotalRooms.ToString()
        lblOverall.Text = dblOverallOccupancy.ToString("p")
    End Sub

    Private Sub btnClear_Click(sender As System.Object, e As System.EventArgs) Handles btnClear.Click
        ' Clear the list box and labels.
        lstOutput.Items.Clear()
        lblTotalRooms.Text = String.Empty
        lblOverall.Text = String.Empty
    End Sub

    Private Sub btnExit_Click(sender As System.Object, e As System.EventArgs) Handles btnExit.Click
        ' Close the form.
        Me.Close()
    End Sub
End Class
