Public Class MainForm
    ' This program checks what the user selected and returns a price by using multiple from.
    ' Author: Christian Carreras

    Private Sub btnSelect_Click(sender As System.Object, e As System.EventArgs) Handles btnSelect.Click
        ' Create new from.
        Dim frmConferenceOptions As New ConferenceOptions

        ' Make sure all the text boxes are filled out.
        If txtName.Text = String.Empty Or txtCompany.Text = String.Empty Or txtAddress.Text = String.Empty _
            Or txtCity.Text = String.Empty Or txtEmail.Text = String.Empty Or txtState.Text = String.Empty _
            Or txtPhone.Text = String.Empty Or txtZip.Text = String.Empty Then
            MessageBox.Show("Please fill out everything in its entirety.")

        Else
            ' Once the text boxes are all full, the form will open.
            frmConferenceOptions.ShowDialog()
        End If
    End Sub

    Private Sub btnReset_Click(sender As System.Object, e As System.EventArgs) Handles btnReset.Click
        ' This button will reset all the text boxes and labels.
        txtName.Text = String.Empty
        txtCompany.Text = String.Empty
        txtAddress.Text = String.Empty
        txtCity.Text = String.Empty
        txtPhone.Text = String.Empty
        txtEmail.Text = String.Empty
        txtState.Text = String.Empty
        txtZip.Text = String.Empty
        lblTotal.Text = String.Empty
    End Sub

    Private Sub btnExit_Click(sender As System.Object, e As System.EventArgs) Handles btnExit.Click
        ' Close the form.
        Me.Close()
    End Sub
End Class
