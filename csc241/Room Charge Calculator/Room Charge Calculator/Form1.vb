Public Class Form1

    Private Sub btnCalculate_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCalculate.Click
        ' Declare variables for the calculations.
        Dim decRoomCharges As Decimal           ' Room charge total
        Dim decAddCharges As Decimal            ' Additional charges
        Dim decSubtotal As Decimal              ' Subtotal
        Dim decTax As Decimal                   ' Tax
        Dim decTotal As Decimal                 ' Total of all charges
        Const decTAX_RATE As Decimal = 0.08D    ' Tax rate

        Try
            ' Calculate and display the additional the room charges.
            decRoomCharges = CDec(txtNights.Text) * CDec(txtNightlyCharge.Text)
            lblRoomCharges.Text = decRoomCharges.ToString("c")

            'Calculate and display the additional charges.
            decAddCharges = CDec(txtRoomService.Text) + CDec(txtTelephone.Text) + CDec(txtMisc.Text)
            lblAddCharges.Text = decAddCharges.ToString("c")

            'Calculate and display the subtotal.
            decSubtotal = decRoomCharges + decAddCharges
            lblSubtotal.Text = decSubtotal.ToString("c")

            'Calculate and display the tax.
            decTax = decSubtotal * decTAX_RATE
            lblTax.Text = decTax.ToString("c")

            'Calculate and display the total charges.
            decTotal = decSubtotal + decTax
            lblTotal.Text = decTotal.ToString("c")

            ' Change the colors for the total charges.
            lblTotal.BackColor = Color.Blue
            lblTotal.ForeColor = Color.White
        Catch
            ' Error Message
            MessageBox.Show("All input must be valid numerical values.")

        End Try
    End Sub

    Private Sub btnClear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClear.Click
        ' Clear the room info fields.
        txtNights.Clear()
        txtNightlyCharge.Clear()

        ' Clear the additional charges fields.
        txtRoomService.Clear()
        txtTelephone.Clear()
        txtMisc.Clear()

        ' Clear the decTotal fields.
        lblRoomCharges.Text = String.Empty
        lblAddCharges.Text = String.Empty
        lblSubtotal.Text = String.Empty
        lblTax.Text = String.Empty
        lblTotal.Text = String.Empty

        ' Get today's date from the operating system and display it.
        lblDateToday.Text = Now.ToString("D")

        ' Get the current time from the operating system and display it.
        lblTimeToday.Text = Now.ToString("T")

        ' Reset the focus to the first field.
        txtNights.Focus()

        ' Reset the lblTotal control's colors.
        lblTotal.BackColor = SystemColors.Control
        lblTotal.ForeColor = SystemColors.Control

    End Sub

    Private Sub btnExit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnExit.Click
        ' Close the form.
        Me.Close()
    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' Get today's date from the system displaying it.
        lblDateToday.Text = Now.ToString("D")

        ' Get the current time from the system displaying it.
        lblTimeToday.Text = Now.ToString("T")
    End Sub
End Class
