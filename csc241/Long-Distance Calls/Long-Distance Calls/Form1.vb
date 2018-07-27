Public Class Form1
    ' This program calculates the charge of a phone call
    ' per minute by using specific rates
    ' Author: Christian Carreras

    Const dblDAY_TIME As Double = 0.07  ' Rate for the daytime
    Const dblEVENING As Double = 0.12   ' Rate for the evening
    Const dblOFF_PEAK As Double = 0.05  ' Rate for off-peak

    Private Sub btnCalculate_Click(sender As System.Object, e As System.EventArgs) Handles btnCalculate.Click
        Dim intMinutes As Integer   ' Minutes the phone call lasted
        Dim dblCharge As Double     ' Charge of phone call

        ' Check if the value entered was a number.
        If Integer.TryParse(txtMinutes.Text, intMinutes) Then

            If radDaytime.Checked = True Then
                ' If the user selected the daytime radio button.
                dblCharge = intMinutes * dblDAY_TIME
                lblCharge.Text = dblCharge.ToString("c")

            ElseIf radEvening.Checked = True Then
                ' If the user selected the evening radio button.
                dblCharge = intMinutes * dblEVENING
                lblCharge.Text = dblCharge.ToString("c")

            Else
                ' If the user selected the off-peak radio button.
                dblCharge = intMinutes * dblOFF_PEAK
                lblCharge.Text = dblCharge.ToString("c")
            End If

        Else
            ' If the value entered is not an integer.
            MessageBox.Show("Please enter a integer value.")
        End If
    End Sub

    Private Sub btnClear_Click(sender As System.Object, e As System.EventArgs) Handles btnClear.Click
        ' Clear the text box and label. Give focus to the text box and check the Daytime radio button.
        txtMinutes.Clear()
        lblCharge.Text = String.Empty
        radDaytime.Checked = True
        txtMinutes.Focus()
    End Sub

    Private Sub btnExit_Click(sender As System.Object, e As System.EventArgs) Handles btnExit.Click
        ' Close the form
        Me.Close()
    End Sub
End Class
