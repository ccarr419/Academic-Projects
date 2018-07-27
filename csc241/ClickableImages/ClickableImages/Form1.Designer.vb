<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.btnFive = New System.Windows.Forms.Button()
        Me.btnFour = New System.Windows.Forms.Button()
        Me.btnThree = New System.Windows.Forms.Button()
        Me.btnTwo = New System.Windows.Forms.Button()
        Me.btnOne = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'btnFive
        '
        Me.btnFive.Image = Global.ClickableImages.My.Resources.Resources.Five
        Me.btnFive.Location = New System.Drawing.Point(327, 21)
        Me.btnFive.Name = "btnFive"
        Me.btnFive.Size = New System.Drawing.Size(59, 89)
        Me.btnFive.TabIndex = 4
        Me.btnFive.UseVisualStyleBackColor = True
        '
        'btnFour
        '
        Me.btnFour.Image = Global.ClickableImages.My.Resources.Resources.Four
        Me.btnFour.Location = New System.Drawing.Point(248, 21)
        Me.btnFour.Name = "btnFour"
        Me.btnFour.Size = New System.Drawing.Size(59, 89)
        Me.btnFour.TabIndex = 3
        Me.btnFour.UseVisualStyleBackColor = True
        '
        'btnThree
        '
        Me.btnThree.Image = Global.ClickableImages.My.Resources.Resources.Three
        Me.btnThree.Location = New System.Drawing.Point(167, 21)
        Me.btnThree.Name = "btnThree"
        Me.btnThree.Size = New System.Drawing.Size(59, 89)
        Me.btnThree.TabIndex = 2
        Me.btnThree.UseVisualStyleBackColor = True
        '
        'btnTwo
        '
        Me.btnTwo.Image = Global.ClickableImages.My.Resources.Resources.Two
        Me.btnTwo.Location = New System.Drawing.Point(90, 21)
        Me.btnTwo.Name = "btnTwo"
        Me.btnTwo.Size = New System.Drawing.Size(59, 89)
        Me.btnTwo.TabIndex = 1
        Me.btnTwo.UseVisualStyleBackColor = True
        '
        'btnOne
        '
        Me.btnOne.Image = Global.ClickableImages.My.Resources.Resources.One
        Me.btnOne.Location = New System.Drawing.Point(12, 21)
        Me.btnOne.Name = "btnOne"
        Me.btnOne.Size = New System.Drawing.Size(59, 89)
        Me.btnOne.TabIndex = 0
        Me.btnOne.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(398, 128)
        Me.Controls.Add(Me.btnFive)
        Me.Controls.Add(Me.btnFour)
        Me.Controls.Add(Me.btnThree)
        Me.Controls.Add(Me.btnTwo)
        Me.Controls.Add(Me.btnOne)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents btnOne As System.Windows.Forms.Button
    Friend WithEvents btnTwo As System.Windows.Forms.Button
    Friend WithEvents btnThree As System.Windows.Forms.Button
    Friend WithEvents btnFour As System.Windows.Forms.Button
    Friend WithEvents btnFive As System.Windows.Forms.Button

End Class
