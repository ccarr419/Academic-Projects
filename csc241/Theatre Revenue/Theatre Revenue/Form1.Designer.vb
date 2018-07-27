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
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.txtAdultTicketsSold = New System.Windows.Forms.TextBox()
        Me.txtAdultTicketPrice = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.txtChildTicketsSold = New System.Windows.Forms.TextBox()
        Me.txtChildTicketsPrice = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.GroupBox3 = New System.Windows.Forms.GroupBox()
        Me.lblGrossTotal = New System.Windows.Forms.Label()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.lblGrossChildTicketSales = New System.Windows.Forms.Label()
        Me.lblGrossAdultTicketSales = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.GroupBox4 = New System.Windows.Forms.GroupBox()
        Me.lblNetTotal = New System.Windows.Forms.Label()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.lblNetChildTicketSales = New System.Windows.Forms.Label()
        Me.lblNetAdultTicketSales = New System.Windows.Forms.Label()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.Label13 = New System.Windows.Forms.Label()
        Me.btnCalculate = New System.Windows.Forms.Button()
        Me.btnClear = New System.Windows.Forms.Button()
        Me.btnExit = New System.Windows.Forms.Button()
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.GroupBox4.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.txtAdultTicketsSold)
        Me.GroupBox1.Controls.Add(Me.txtAdultTicketPrice)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Location = New System.Drawing.Point(12, 12)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(258, 119)
        Me.GroupBox1.TabIndex = 0
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Adult Tickets Sales"
        '
        'txtAdultTicketsSold
        '
        Me.txtAdultTicketsSold.Location = New System.Drawing.Point(118, 65)
        Me.txtAdultTicketsSold.Name = "txtAdultTicketsSold"
        Me.txtAdultTicketsSold.Size = New System.Drawing.Size(100, 20)
        Me.txtAdultTicketsSold.TabIndex = 3
        '
        'txtAdultTicketPrice
        '
        Me.txtAdultTicketPrice.Location = New System.Drawing.Point(118, 34)
        Me.txtAdultTicketPrice.Name = "txtAdultTicketPrice"
        Me.txtAdultTicketPrice.Size = New System.Drawing.Size(100, 20)
        Me.txtAdultTicketPrice.TabIndex = 2
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(43, 68)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(69, 13)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "Tickets Sold;"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(26, 37)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(86, 13)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Price Per Ticket:"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.txtChildTicketsSold)
        Me.GroupBox2.Controls.Add(Me.txtChildTicketsPrice)
        Me.GroupBox2.Controls.Add(Me.Label3)
        Me.GroupBox2.Controls.Add(Me.Label4)
        Me.GroupBox2.Location = New System.Drawing.Point(284, 12)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(258, 119)
        Me.GroupBox2.TabIndex = 1
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Child Tickets Sales"
        '
        'txtChildTicketsSold
        '
        Me.txtChildTicketsSold.Location = New System.Drawing.Point(118, 65)
        Me.txtChildTicketsSold.Name = "txtChildTicketsSold"
        Me.txtChildTicketsSold.Size = New System.Drawing.Size(100, 20)
        Me.txtChildTicketsSold.TabIndex = 3
        '
        'txtChildTicketsPrice
        '
        Me.txtChildTicketsPrice.Location = New System.Drawing.Point(118, 34)
        Me.txtChildTicketsPrice.Name = "txtChildTicketsPrice"
        Me.txtChildTicketsPrice.Size = New System.Drawing.Size(100, 20)
        Me.txtChildTicketsPrice.TabIndex = 2
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(43, 68)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(69, 13)
        Me.Label3.TabIndex = 1
        Me.Label3.Text = "Tickets Sold;"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(26, 37)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(86, 13)
        Me.Label4.TabIndex = 0
        Me.Label4.Text = "Price Per Ticket:"
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.lblGrossTotal)
        Me.GroupBox3.Controls.Add(Me.Label9)
        Me.GroupBox3.Controls.Add(Me.lblGrossChildTicketSales)
        Me.GroupBox3.Controls.Add(Me.lblGrossAdultTicketSales)
        Me.GroupBox3.Controls.Add(Me.Label5)
        Me.GroupBox3.Controls.Add(Me.Label6)
        Me.GroupBox3.Location = New System.Drawing.Point(12, 137)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(258, 151)
        Me.GroupBox3.TabIndex = 2
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "Gross Ticket Revenue"
        '
        'lblGrossTotal
        '
        Me.lblGrossTotal.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblGrossTotal.Location = New System.Drawing.Point(118, 99)
        Me.lblGrossTotal.Name = "lblGrossTotal"
        Me.lblGrossTotal.Size = New System.Drawing.Size(100, 23)
        Me.lblGrossTotal.TabIndex = 5
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(49, 109)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(64, 13)
        Me.Label9.TabIndex = 4
        Me.Label9.Text = "Total Gross:"
        '
        'lblGrossChildTicketSales
        '
        Me.lblGrossChildTicketSales.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblGrossChildTicketSales.Location = New System.Drawing.Point(118, 67)
        Me.lblGrossChildTicketSales.Name = "lblGrossChildTicketSales"
        Me.lblGrossChildTicketSales.Size = New System.Drawing.Size(100, 23)
        Me.lblGrossChildTicketSales.TabIndex = 3
        '
        'lblGrossAdultTicketSales
        '
        Me.lblGrossAdultTicketSales.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblGrossAdultTicketSales.Location = New System.Drawing.Point(118, 36)
        Me.lblGrossAdultTicketSales.Name = "lblGrossAdultTicketSales"
        Me.lblGrossAdultTicketSales.Size = New System.Drawing.Size(100, 23)
        Me.lblGrossAdultTicketSales.TabIndex = 2
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(17, 77)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(95, 13)
        Me.Label5.TabIndex = 1
        Me.Label5.Text = "Child Ticket Sales:"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(17, 46)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(96, 13)
        Me.Label6.TabIndex = 0
        Me.Label6.Text = "Adult Ticket Sales:"
        '
        'GroupBox4
        '
        Me.GroupBox4.Controls.Add(Me.lblNetTotal)
        Me.GroupBox4.Controls.Add(Me.Label8)
        Me.GroupBox4.Controls.Add(Me.lblNetChildTicketSales)
        Me.GroupBox4.Controls.Add(Me.lblNetAdultTicketSales)
        Me.GroupBox4.Controls.Add(Me.Label12)
        Me.GroupBox4.Controls.Add(Me.Label13)
        Me.GroupBox4.Location = New System.Drawing.Point(284, 137)
        Me.GroupBox4.Name = "GroupBox4"
        Me.GroupBox4.Size = New System.Drawing.Size(258, 151)
        Me.GroupBox4.TabIndex = 3
        Me.GroupBox4.TabStop = False
        Me.GroupBox4.Text = "Net Ticket Revenue"
        '
        'lblNetTotal
        '
        Me.lblNetTotal.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblNetTotal.Location = New System.Drawing.Point(118, 99)
        Me.lblNetTotal.Name = "lblNetTotal"
        Me.lblNetTotal.Size = New System.Drawing.Size(100, 23)
        Me.lblNetTotal.TabIndex = 5
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(13, 99)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(99, 26)
        Me.Label8.TabIndex = 4
        Me.Label8.Text = "Total Net Revenue" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "     for Ticket Sales:"
        '
        'lblNetChildTicketSales
        '
        Me.lblNetChildTicketSales.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblNetChildTicketSales.Location = New System.Drawing.Point(118, 67)
        Me.lblNetChildTicketSales.Name = "lblNetChildTicketSales"
        Me.lblNetChildTicketSales.Size = New System.Drawing.Size(100, 23)
        Me.lblNetChildTicketSales.TabIndex = 3
        '
        'lblNetAdultTicketSales
        '
        Me.lblNetAdultTicketSales.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblNetAdultTicketSales.Location = New System.Drawing.Point(118, 36)
        Me.lblNetAdultTicketSales.Name = "lblNetAdultTicketSales"
        Me.lblNetAdultTicketSales.Size = New System.Drawing.Size(100, 23)
        Me.lblNetAdultTicketSales.TabIndex = 2
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(17, 77)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(95, 13)
        Me.Label12.TabIndex = 1
        Me.Label12.Text = "Child Ticket Sales:"
        '
        'Label13
        '
        Me.Label13.AutoSize = True
        Me.Label13.Location = New System.Drawing.Point(17, 46)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(96, 13)
        Me.Label13.TabIndex = 0
        Me.Label13.Text = "Adult Ticket Sales:"
        '
        'btnCalculate
        '
        Me.btnCalculate.Location = New System.Drawing.Point(92, 316)
        Me.btnCalculate.Name = "btnCalculate"
        Me.btnCalculate.Size = New System.Drawing.Size(106, 38)
        Me.btnCalculate.TabIndex = 4
        Me.btnCalculate.Text = "&Calculate Ticket" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "Revenue" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10)
        Me.btnCalculate.UseVisualStyleBackColor = True
        '
        'btnClear
        '
        Me.btnClear.Location = New System.Drawing.Point(225, 316)
        Me.btnClear.Name = "btnClear"
        Me.btnClear.Size = New System.Drawing.Size(106, 38)
        Me.btnClear.TabIndex = 5
        Me.btnClear.Text = "Clea&r"
        Me.btnClear.UseVisualStyleBackColor = True
        '
        'btnExit
        '
        Me.btnExit.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.btnExit.Location = New System.Drawing.Point(360, 316)
        Me.btnExit.Name = "btnExit"
        Me.btnExit.Size = New System.Drawing.Size(106, 38)
        Me.btnExit.TabIndex = 6
        Me.btnExit.Text = "E&xit"
        Me.btnExit.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AcceptButton = Me.btnCalculate
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.CancelButton = Me.btnExit
        Me.ClientSize = New System.Drawing.Size(554, 380)
        Me.Controls.Add(Me.btnExit)
        Me.Controls.Add(Me.btnClear)
        Me.Controls.Add(Me.btnCalculate)
        Me.Controls.Add(Me.GroupBox4)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Name = "Form1"
        Me.Text = "Theatre Revenue"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.GroupBox3.ResumeLayout(False)
        Me.GroupBox3.PerformLayout()
        Me.GroupBox4.ResumeLayout(False)
        Me.GroupBox4.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents txtAdultTicketsSold As System.Windows.Forms.TextBox
    Friend WithEvents txtAdultTicketPrice As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents txtChildTicketsSold As System.Windows.Forms.TextBox
    Friend WithEvents txtChildTicketsPrice As System.Windows.Forms.TextBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents lblGrossChildTicketSales As System.Windows.Forms.Label
    Friend WithEvents lblGrossAdultTicketSales As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents lblGrossTotal As System.Windows.Forms.Label
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents GroupBox4 As System.Windows.Forms.GroupBox
    Friend WithEvents lblNetTotal As System.Windows.Forms.Label
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents lblNetChildTicketSales As System.Windows.Forms.Label
    Friend WithEvents lblNetAdultTicketSales As System.Windows.Forms.Label
    Friend WithEvents Label12 As System.Windows.Forms.Label
    Friend WithEvents Label13 As System.Windows.Forms.Label
    Friend WithEvents btnCalculate As System.Windows.Forms.Button
    Friend WithEvents btnClear As System.Windows.Forms.Button
    Friend WithEvents btnExit As System.Windows.Forms.Button

End Class
