Public Class Form1

    Private Sub btnCalculate_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCalculate.Click
        ' Declare variables to calculate the ticket sales.
        Const THEATRE_CUT = 0.2                     ' The amount of money the theatre keeps.
        Dim decGrossAdultTicketSales As Decimal     ' The total amount of money received from adult tickets.
        Dim decGrossChildTicketSales As Decimal     ' The total amount of money received from child tickets.
        Dim decGrossTotal As Decimal                ' The total amount of money received from all tickets.
        Dim decNetAdultTicketSales As Decimal       ' The money left from adult tickets after the theatres cut.
        Dim decNetChildTicketSales As Decimal       ' The money left from child tickets after the theatres cut.
        Dim decNetTotal As Decimal                  ' The total money left from all tickets after the theatres cut.

        Try
            ' Calculate the gross adult ticket sales.
            decGrossAdultTicketSales = CDec(txtAdultTicketPrice.Text) * CInt(txtAdultTicketsSold.Text)
            lblGrossAdultTicketSales.Text = decGrossAdultTicketSales.ToString("c")

            ' Calculate the gross child ticket sales.
            decGrossChildTicketSales = CDec(txtChildTicketsPrice.Text) * CInt(txtChildTicketsSold.Text)
            lblGrossChildTicketSales.Text = decGrossChildTicketSales.ToString("c")

            ' Calculate the total gross sales.
            decGrossTotal = decGrossAdultTicketSales + decGrossChildTicketSales
            lblGrossTotal.Text = decGrossTotal.ToString("c")

            ' Calculate the total net adult ticket sales.
            decNetAdultTicketSales = decGrossAdultTicketSales * THEATRE_CUT
            lblNetAdultTicketSales.Text = decNetAdultTicketSales.ToString("c")

            ' Calculate the total net child ticket sales.
            decNetChildTicketSales = decGrossChildTicketSales * THEATRE_CUT
            lblNetChildTicketSales.Text = decNetChildTicketSales.ToString("c")

            ' Calculate the total net sales.
            decNetTotal = decGrossTotal * THEATRE_CUT
            lblNetTotal.Text = decNetTotal.ToString("c")

        Catch
            ' Error Message
            MessageBox.Show("All input must be valid numeric values.")

        End Try
    End Sub

    Private Sub btnClear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClear.Click
        ' Clear the text boxes
        txtAdultTicketPrice.Clear()     ' Clears the Price Per Ticket text box in the Adult Ticket Sales group box.
        txtAdultTicketsSold.Clear()     ' Clears the Tickets Sold text box in the Adult Ticket Sales group box.
        txtChildTicketsPrice.Clear()    ' Clears the Price Per Ticket text box in the Child Ticket Sales group box.
        txtChildTicketsSold.Clear()     ' Clears the Tickets Sold text box in the Child Ticket Sales group box.

        ' Clear the lables
        lblGrossAdultTicketSales.Text = String.Empty    ' Resets the text in lblGrossAdultTicketSales.
        lblGrossChildTicketSales.Text = String.Empty    ' Resets the text in lblGrossChildTicketSales.
        lblGrossTotal.Text = String.Empty               ' Resets the text in lblGrossTotal.
        lblNetAdultTicketSales.Text = String.Empty      ' Resets the text in lblNetAdultTicketSales.
        lblNetChildTicketSales.Text = String.Empty      ' Resets the text in lblNetChildTicketSales.
        lblNetTotal.Text = String.Empty                 ' Resets the text in lblNetTotal.

        ' Sets the focus
        txtAdultTicketPrice.Focus()
    End Sub

    Private Sub btnExit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnExit.Click
        ' Closes the form
        Me.Close()
    End Sub
End Class
