Public Class ConferenceOptions

    ' Constant class-level variables
    Const intCONFERENCE_REG As Integer = 895    ' Price for the conference registration
    Const intINTRO_TO_E_COMM As Integer = 295   ' Price for Introduction to E-commerce workshop
    Const intTHE_FUTURE As Integer = 295        ' Price for The Future of the Web workshop
    Const intADVANCED_VB As Integer = 395       ' Price for Advanced Visual Basic workshop
    Const intNETWORK As Integer = 395           ' Price for Network Security workshop
    Const intDINNER As Integer = 30             ' Price for the opening night dinner & keynote

    Private Sub btnClose_Click(sender As System.Object, e As System.EventArgs) Handles btnClose.Click
        Dim intTotal As Integer = 0 ' The total amount to be paid

        ' If statements to determine what the user selected.
        If chkConference.Checked = True Then
            intTotal += intCONFERENCE_REG

            If chkOpeningNight.Checked = True Then
                intTotal += intDINNER

                If lstWorkshops.Text = "Intro to E-Commerce" Then
                    intTotal += intINTRO_TO_E_COMM

                ElseIf lstWorkshops.Text = "The Future of the Web" Then
                    intTotal += intTHE_FUTURE

                ElseIf lstWorkshops.Text = "Advanced Visual Basic" Then
                    intTotal += intADVANCED_VB

                ElseIf lstWorkshops.Text = "Network Security" Then
                    intTotal += intNETWORK
                End If

            Else
                If lstWorkshops.Text = "Intro to E-Commerce" Then
                    intTotal += intINTRO_TO_E_COMM

                ElseIf lstWorkshops.Text = "The Future of the Web" Then
                    intTotal += intTHE_FUTURE

                ElseIf lstWorkshops.Text = "Advanced Visual Basic" Then
                    intTotal += intADVANCED_VB

                ElseIf lstWorkshops.Text = "Network Security" Then
                    intTotal += intNETWORK
                End If

            End If

        ElseIf chkConference.Checked = False Then

            If chkOpeningNight.Checked = True Then
                intTotal += intDINNER

                If lstWorkshops.Text = "Intro to E-Commerce" Then
                    intTotal += intINTRO_TO_E_COMM

                ElseIf lstWorkshops.Text = "The Future of the Web" Then
                    intTotal += intTHE_FUTURE

                ElseIf lstWorkshops.Text = "Advanced Visual Basic" Then
                    intTotal += intADVANCED_VB

                ElseIf lstWorkshops.Text = "Network Security" Then
                    intTotal += intNETWORK
                End If
            Else
                If lstWorkshops.Text = "Intro to E-Commerce" Then
                    intTotal += intINTRO_TO_E_COMM

                ElseIf lstWorkshops.Text = "The Future of the Web" Then
                    intTotal += intTHE_FUTURE

                ElseIf lstWorkshops.Text = "Advanced Visual Basic" Then
                    intTotal += intADVANCED_VB

                ElseIf lstWorkshops.Text = "Network Security" Then
                    intTotal += intNETWORK
                End If
            End If
        End If

        ' Close the form and put the the total in the total label.
        MainForm.lblTotal.Text = intTotal.ToString("c")
        Me.Close()

    End Sub

    Private Sub btnReset_Click(sender As System.Object, e As System.EventArgs) Handles btnReset.Click
        ' Reset all selections.
        chkConference.Checked = False
        chkOpeningNight.Checked = False
        lstWorkshops.SelectedIndex = -1
    End Sub
End Class