VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomctl.ocx"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "EPROM Pin Swapper v1.0 | 2012 by Farid"
   ClientHeight    =   6615
   ClientLeft      =   5160
   ClientTop       =   2505
   ClientWidth     =   4935
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6615
   ScaleWidth      =   4935
   Begin MSComctlLib.ProgressBar ProgressBar1 
      Height          =   375
      Left            =   1680
      TabIndex        =   68
      Top             =   5640
      Width           =   1575
      _ExtentX        =   2778
      _ExtentY        =   661
      _Version        =   393216
      Appearance      =   1
   End
   Begin VB.ComboBox Combo7 
      Enabled         =   0   'False
      Height          =   315
      Left            =   3840
      TabIndex        =   66
      Text            =   "VCC"
      Top             =   480
      Width           =   735
   End
   Begin VB.ComboBox Combo6 
      Enabled         =   0   'False
      Height          =   315
      Left            =   3840
      TabIndex        =   65
      Text            =   "/OE"
      Top             =   3360
      Width           =   735
   End
   Begin VB.ComboBox Combo5 
      Enabled         =   0   'False
      Height          =   315
      Left            =   3840
      TabIndex        =   64
      Text            =   "/CE"
      Top             =   4080
      Width           =   735
   End
   Begin VB.ComboBox Combo4 
      Enabled         =   0   'False
      Height          =   315
      Left            =   360
      TabIndex        =   63
      Text            =   "GND"
      Top             =   5880
      Width           =   735
   End
   Begin VB.ComboBox Combo3 
      Enabled         =   0   'False
      Height          =   315
      Index           =   7
      ItemData        =   "Form1.frx":0352
      Left            =   3840
      List            =   "Form1.frx":036E
      TabIndex        =   62
      Top             =   4440
      Width           =   735
   End
   Begin VB.ComboBox Combo3 
      Enabled         =   0   'False
      Height          =   315
      Index           =   6
      ItemData        =   "Form1.frx":0392
      Left            =   3840
      List            =   "Form1.frx":03AE
      TabIndex        =   61
      Top             =   4800
      Width           =   735
   End
   Begin VB.ComboBox Combo3 
      Enabled         =   0   'False
      Height          =   315
      Index           =   5
      ItemData        =   "Form1.frx":03D2
      Left            =   3840
      List            =   "Form1.frx":03EE
      TabIndex        =   60
      Top             =   5160
      Width           =   735
   End
   Begin VB.ComboBox Combo3 
      Enabled         =   0   'False
      Height          =   315
      Index           =   4
      ItemData        =   "Form1.frx":0412
      Left            =   3840
      List            =   "Form1.frx":042E
      TabIndex        =   59
      Top             =   5520
      Width           =   735
   End
   Begin VB.ComboBox Combo3 
      Enabled         =   0   'False
      Height          =   315
      Index           =   3
      ItemData        =   "Form1.frx":0452
      Left            =   3840
      List            =   "Form1.frx":046E
      TabIndex        =   58
      Top             =   5880
      Width           =   735
   End
   Begin VB.ComboBox Combo3 
      Enabled         =   0   'False
      Height          =   315
      Index           =   2
      ItemData        =   "Form1.frx":0492
      Left            =   360
      List            =   "Form1.frx":04AE
      TabIndex        =   57
      Top             =   5520
      Width           =   735
   End
   Begin VB.ComboBox Combo3 
      Enabled         =   0   'False
      Height          =   315
      Index           =   1
      ItemData        =   "Form1.frx":04D2
      Left            =   360
      List            =   "Form1.frx":04EE
      TabIndex        =   56
      Top             =   5160
      Width           =   735
   End
   Begin VB.ComboBox Combo3 
      Enabled         =   0   'False
      Height          =   315
      Index           =   0
      ItemData        =   "Form1.frx":0512
      Left            =   360
      List            =   "Form1.frx":052E
      TabIndex        =   55
      Top             =   4800
      Width           =   735
   End
   Begin MSComDlg.CommonDialog CommonDialog2 
      Left            =   2280
      Top             =   4320
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Save"
      Enabled         =   0   'False
      Height          =   375
      Left            =   1920
      TabIndex        =   54
      Top             =   3720
      Width           =   1095
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Open"
      Height          =   375
      Left            =   1920
      TabIndex        =   53
      Top             =   2400
      Width           =   1095
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   2280
      Top             =   1800
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   19
      ItemData        =   "Form1.frx":0552
      Left            =   3840
      List            =   "Form1.frx":0592
      TabIndex        =   52
      Top             =   840
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   18
      ItemData        =   "Form1.frx":05F0
      Left            =   3840
      List            =   "Form1.frx":0630
      TabIndex        =   51
      Top             =   1200
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   17
      ItemData        =   "Form1.frx":068E
      Left            =   3840
      List            =   "Form1.frx":06CE
      TabIndex        =   50
      Top             =   1560
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   16
      ItemData        =   "Form1.frx":072C
      Left            =   3840
      List            =   "Form1.frx":076C
      TabIndex        =   49
      Top             =   1920
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   15
      ItemData        =   "Form1.frx":07CA
      Left            =   3840
      List            =   "Form1.frx":080A
      TabIndex        =   48
      Top             =   2280
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   14
      ItemData        =   "Form1.frx":0868
      Left            =   3840
      List            =   "Form1.frx":08A8
      TabIndex        =   47
      Top             =   2640
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   13
      ItemData        =   "Form1.frx":0906
      Left            =   3840
      List            =   "Form1.frx":0946
      TabIndex        =   46
      Top             =   3000
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   12
      ItemData        =   "Form1.frx":09A4
      Left            =   3840
      List            =   "Form1.frx":09E4
      TabIndex        =   45
      Top             =   3720
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   11
      ItemData        =   "Form1.frx":0A42
      Left            =   360
      List            =   "Form1.frx":0A82
      TabIndex        =   44
      Top             =   4440
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   0
      ItemData        =   "Form1.frx":0AE0
      Left            =   360
      List            =   "Form1.frx":0B20
      TabIndex        =   43
      Top             =   480
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   10
      ItemData        =   "Form1.frx":0B7E
      Left            =   360
      List            =   "Form1.frx":0BBE
      TabIndex        =   10
      Top             =   4080
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   9
      ItemData        =   "Form1.frx":0C1C
      Left            =   360
      List            =   "Form1.frx":0C5C
      TabIndex        =   9
      Top             =   3720
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   8
      ItemData        =   "Form1.frx":0CBA
      Left            =   360
      List            =   "Form1.frx":0CFA
      TabIndex        =   8
      Top             =   3360
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   7
      ItemData        =   "Form1.frx":0D58
      Left            =   360
      List            =   "Form1.frx":0D98
      TabIndex        =   7
      Top             =   3000
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   6
      ItemData        =   "Form1.frx":0DF6
      Left            =   360
      List            =   "Form1.frx":0E36
      TabIndex        =   6
      Top             =   2640
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   5
      ItemData        =   "Form1.frx":0E94
      Left            =   360
      List            =   "Form1.frx":0ED4
      TabIndex        =   5
      Top             =   2280
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   4
      ItemData        =   "Form1.frx":0F32
      Left            =   360
      List            =   "Form1.frx":0F72
      TabIndex        =   4
      Top             =   1920
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   3
      ItemData        =   "Form1.frx":0FD0
      Left            =   360
      List            =   "Form1.frx":1010
      TabIndex        =   3
      Top             =   1560
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   2
      ItemData        =   "Form1.frx":106E
      Left            =   360
      List            =   "Form1.frx":10AE
      TabIndex        =   2
      Top             =   1200
      Width           =   735
   End
   Begin VB.ComboBox Combo2 
      Enabled         =   0   'False
      Height          =   315
      Index           =   1
      ItemData        =   "Form1.frx":110C
      Left            =   360
      List            =   "Form1.frx":114C
      TabIndex        =   1
      Top             =   840
      Width           =   735
   End
   Begin VB.ComboBox Combo1 
      DataField       =   "1"
      DataMember      =   "1"
      Enabled         =   0   'False
      Height          =   315
      ItemData        =   "Form1.frx":11AA
      Left            =   1680
      List            =   "Form1.frx":11AC
      TabIndex        =   0
      Text            =   "Target Chip"
      Top             =   3120
      Width           =   1575
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      Height          =   255
      Left            =   2040
      TabIndex        =   69
      Top             =   5280
      Width           =   855
   End
   Begin VB.Label Label2 
      Height          =   375
      Left            =   2040
      TabIndex        =   67
      Top             =   0
      Width           =   855
   End
   Begin VB.Shape Shape2 
      Height          =   855
      Left            =   2040
      Shape           =   3  'Circle
      Top             =   0
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "32"
      Height          =   255
      Index           =   32
      Left            =   3360
      TabIndex        =   42
      Top             =   480
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "31"
      Height          =   255
      Index           =   31
      Left            =   3360
      TabIndex        =   41
      Top             =   840
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "30"
      Height          =   255
      Index           =   30
      Left            =   3360
      TabIndex        =   40
      Top             =   1200
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "29"
      Height          =   255
      Index           =   29
      Left            =   3360
      TabIndex        =   39
      Top             =   1560
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "28"
      Height          =   255
      Index           =   28
      Left            =   3360
      TabIndex        =   38
      Top             =   1920
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "27"
      Height          =   255
      Index           =   27
      Left            =   3360
      TabIndex        =   37
      Top             =   2280
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "26"
      Height          =   255
      Index           =   26
      Left            =   3360
      TabIndex        =   36
      Top             =   2640
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "25"
      Height          =   255
      Index           =   25
      Left            =   3360
      TabIndex        =   35
      Top             =   3000
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "24"
      Height          =   255
      Index           =   24
      Left            =   3360
      TabIndex        =   34
      Top             =   3360
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "23"
      Height          =   255
      Index           =   23
      Left            =   3360
      TabIndex        =   33
      Top             =   3720
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "22"
      Height          =   255
      Index           =   22
      Left            =   3360
      TabIndex        =   32
      Top             =   4080
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "21"
      Height          =   255
      Index           =   21
      Left            =   3360
      TabIndex        =   31
      Top             =   4440
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "20"
      Height          =   255
      Index           =   20
      Left            =   3360
      TabIndex        =   30
      Top             =   4800
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "19"
      Height          =   255
      Index           =   19
      Left            =   3360
      TabIndex        =   29
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "18"
      Height          =   255
      Index           =   18
      Left            =   3360
      TabIndex        =   28
      Top             =   5520
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "17"
      Height          =   255
      Index           =   17
      Left            =   3360
      TabIndex        =   27
      Top             =   5880
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "16"
      Height          =   255
      Index           =   16
      Left            =   1320
      TabIndex        =   26
      Top             =   5880
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "15"
      Height          =   255
      Index           =   15
      Left            =   1320
      TabIndex        =   25
      Top             =   5520
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "14"
      Height          =   255
      Index           =   14
      Left            =   1320
      TabIndex        =   24
      Top             =   5160
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "13"
      Height          =   255
      Index           =   13
      Left            =   1320
      TabIndex        =   23
      Top             =   4800
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "12"
      Height          =   255
      Index           =   12
      Left            =   1320
      TabIndex        =   22
      Top             =   4440
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "11"
      Height          =   255
      Index           =   11
      Left            =   1320
      TabIndex        =   21
      Top             =   4080
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "10"
      Height          =   255
      Index           =   10
      Left            =   1320
      TabIndex        =   20
      Top             =   3720
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "09"
      Height          =   255
      Index           =   9
      Left            =   1320
      TabIndex        =   19
      Top             =   3360
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "08"
      Height          =   255
      Index           =   8
      Left            =   1320
      TabIndex        =   18
      Top             =   3000
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "07"
      Height          =   255
      Index           =   7
      Left            =   1320
      TabIndex        =   17
      Top             =   2640
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "06"
      Height          =   255
      Index           =   6
      Left            =   1320
      TabIndex        =   16
      Top             =   2280
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "05"
      Height          =   255
      Index           =   5
      Left            =   1320
      TabIndex        =   15
      Top             =   1920
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "04"
      Height          =   255
      Index           =   4
      Left            =   1320
      TabIndex        =   14
      Top             =   1560
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "03"
      Height          =   255
      Index           =   3
      Left            =   1320
      TabIndex        =   13
      Top             =   1200
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "02"
      Height          =   255
      Index           =   2
      Left            =   1320
      TabIndex        =   12
      Top             =   840
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "01"
      Height          =   255
      Index           =   1
      Left            =   1320
      TabIndex        =   11
      Top             =   480
      Width           =   255
   End
   Begin VB.Shape Shape1 
      Height          =   5895
      Left            =   1200
      Top             =   360
      Width           =   2535
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim file_length As Long
Dim bytes() As Byte
Dim newbytes() As Byte
Dim A() As Integer
Dim B() As Integer
Dim D() As Integer
Dim E() As Integer





Private Sub Combo1_Click()


If Combo2.Count > 0 Then
For j = 0 To 19
For i = (Combo2(j).ListCount - 1) To 0 Step -1
Combo2(j).RemoveItem (i)
Next i
Next j
End If


Combo2(0).Text = "A19"
Combo2(1).Text = "A16"
Combo2(2).Text = "A15"
Combo2(3).Text = "A12"
Combo2(4).Text = "A7"
Combo2(5).Text = "A6"
Combo2(6).Text = "A5"
Combo2(7).Text = "A4"
Combo2(8).Text = "A3"
Combo2(9).Text = "A2"
Combo2(10).Text = "A1"
Combo2(11).Text = "A0"
Combo2(12).Text = "A10"
Combo2(13).Text = "A11"
Combo2(14).Text = "A9"
Combo2(15).Text = "A8"
Combo2(16).Text = "A13"
Combo2(17).Text = "A14"
Combo2(18).Text = "A17"
Combo2(19).Text = "A18"
Combo3(0).Text = "D0"
Combo3(1).Text = "D1"
Combo3(2).Text = "D2"
Combo3(3).Text = "D3"
Combo3(4).Text = "D4"
Combo3(5).Text = "D5"
Combo3(6).Text = "D6"
Combo3(7).Text = "D7"

For i = 0 To 7
Combo3(i).Enabled = True
Next i






Select Case file_length

Case 131072
For j = 0 To 19
For i = 0 To 16
Combo2(j).AddItem "A" & i
Combo2(j).Enabled = True
Next i
Next j
Combo2(0).Text = "VPP"
Combo2(0).Enabled = False
Combo2(19).Text = "/PGM"
Combo2(19).Enabled = False
Combo2(18).Text = "NC"
Combo2(18).Enabled = False

Case 262144
For j = 0 To 19
For i = 0 To 17
Combo2(j).AddItem "A" & i
Combo2(j).Enabled = True
Next i
Next j
Combo2(0).Text = "VPP"
Combo2(0).Enabled = False
Combo2(19).Text = "/PGM"
Combo2(19).Enabled = False

Case 524288
For j = 0 To 19
For i = 0 To 18
Combo2(j).AddItem "A" & i
Combo2(j).Enabled = True
Next i
Next j
Combo2(0).Text = "VPP"
Combo2(0).Enabled = False

Case 1048576
For j = 0 To 19
For i = 0 To 19
Combo2(j).AddItem "A" & i
Combo2(j).Enabled = True
Next i
Next j

End Select







Command2.Enabled = True

End Sub



Private Sub Combo2_Click(Index As Integer)


Select Case Index
Case 0
For i = 0 To (file_length - 1)
B(19, i) = A(Combo2(0).ListIndex, i)
Next i

Case 1
For i = 0 To (file_length - 1)
B(16, i) = A(Combo2(1).ListIndex, i)
Next i

Case 2
For i = 0 To (file_length - 1)
B(15, i) = A(Combo2(2).ListIndex, i)
Next i

Case 3
For i = 0 To (file_length - 1)
B(12, i) = A(Combo2(3).ListIndex, i)
Next i

Case 4
For i = 0 To (file_length - 1)
B(7, i) = A(Combo2(4).ListIndex, i)
Next i

Case 5
For i = 0 To (file_length - 1)
B(6, i) = A(Combo2(5).ListIndex, i)
Next i

Case 6
For i = 0 To (file_length - 1)
B(5, i) = A(Combo2(6).ListIndex, i)
Next i

Case 7
For i = 0 To (file_length - 1)
B(4, i) = A(Combo2(7).ListIndex, i)
Next i

Case 8
For i = 0 To (file_length - 1)
B(3, i) = A(Combo2(8).ListIndex, i)
Next i

Case 9
For i = 0 To (file_length - 1)
B(2, i) = A(Combo2(9).ListIndex, i)
Next i

Case 10
For i = 0 To (file_length - 1)
B(1, i) = A(Combo2(10).ListIndex, i)
Next i

Case 11
For i = 0 To (file_length - 1)
B(0, i) = A(Combo2(11).ListIndex, i)
Next i

Case 12
For i = 0 To (file_length - 1)
B(10, i) = A(Combo2(12).ListIndex, i)
Next i

Case 13
For i = 0 To (file_length - 1)
B(11, i) = A(Combo2(13).ListIndex, i)
Next i

Case 14
For i = 0 To (file_length - 1)
B(9, i) = A(Combo2(14).ListIndex, i)
Next i

Case 15
For i = 0 To (file_length - 1)
B(8, i) = A(Combo2(15).ListIndex, i)
Next i

Case 16
For i = 0 To (file_length - 1)
B(13, i) = A(Combo2(16).ListIndex, i)
Next i

Case 17
For i = 0 To (file_length - 1)
B(14, i) = A(Combo2(17).ListIndex, i)
Next i

Case 18
For i = 0 To (file_length - 1)
B(17, i) = A(Combo2(18).ListIndex, i)
Next i

Case 19
For i = 0 To (file_length - 1)
B(18, i) = A(Combo2(19).ListIndex, i)
Next i

End Select



End Sub

Private Sub Combo3_Click(Index As Integer)
Select Case Index

Case 0
For i = 1 To file_length
E(0, i) = D(Combo3(0).ListIndex, i)
Next i

Case 1
For i = 1 To file_length
E(1, i) = D(Combo3(1).ListIndex, i)
Next i

Case 2
For i = 1 To file_length
E(2, i) = D(Combo3(2).ListIndex, i)
Next i

Case 3
For i = 1 To file_length
E(3, i) = D(Combo3(3).ListIndex, i)
Next i

Case 4
For i = 1 To file_length
E(4, i) = D(Combo3(4).ListIndex, i)
Next i

Case 5
For i = 1 To file_length
E(5, i) = D(Combo3(5).ListIndex, i)
Next i

Case 6
For i = 1 To file_length
E(6, i) = D(Combo3(6).ListIndex, i)
Next i

Case 7
For i = 1 To file_length
E(7, i) = D(Combo3(7).ListIndex, i)
Next i

End Select

End Sub

Private Sub Command1_Click()
CommonDialog1.InitDir = App.Path
CommonDialog1.Filter = "PRG.bin or CHR.bin|*.bin"
CommonDialog1.ShowOpen
If CommonDialog1.Flags = 0 Then Exit Sub

Dim file_name As String
Dim fnum As Long
    file_name = CommonDialog1.FileName
    file_length = FileLen(file_name)
    fnum = FreeFile
    ReDim bytes(1 To file_length)
    Open file_name For Binary As #fnum
    Get #fnum, 1, bytes
    Close fnum
   
If Combo1.ListCount > 0 Then
For i = (Combo1.ListCount - 1) To 0 Step -1
Combo1.RemoveItem (i)
Next i
End If

Select Case file_length

Case 131072
Combo1.AddItem "27C010  128KB"

Case 262144
Combo1.AddItem "27C020  256KB"

Case 524288
Combo1.AddItem "27C040  512KB"

Case 1048576
Combo1.AddItem "27C080  1024KB"

Case Else
MsgBox "Do you want to mess up your EPROM? Check your binary file size!", vbOKOnly, "Oops!"

End Select


Label3.Caption = "Loading"
DoEvents
ProgressBar1.Value = 10
ReDim A(0 To 19, 0 To (file_length - 1)) As Integer
ReDim B(0 To 19, 0 To (file_length - 1)) As Integer
For i = 0 To (file_length - 1)
MA = i
For j = 0 To 19
A(j, i) = MA Mod 2
B(j, i) = A(j, i)
MA = MA \ 2
Next j
If i = file_length / 4 Then ProgressBar1.Value = 25
If i = file_length / 2 Then ProgressBar1.Value = 40
Next i
ProgressBar1.Value = 55
ReDim D(0 To 7, 1 To file_length) As Integer
ReDim E(0 To 7, 1 To file_length) As Integer
For j = 1 To file_length
MA = bytes(j)
For i = 0 To 7
D(i, j) = MA Mod 2
E(i, j) = D(i, j)
MA = MA \ 2
Next i
If j = file_length / 4 Then ProgressBar1.Value = 70
If j = file_length / 2 Then ProgressBar1.Value = 85
Next j
ProgressBar1.Value = 100
Label3.Caption = ""

Combo1.Enabled = True

End Sub

Private Sub Command2_Click()

CommonDialog2.FileName = "Output.bin"
CommonDialog2.Filter = "Binary file (*.bin)"
CommonDialog2.ShowSave
If CommonDialog2.Flags = 0 Then Exit Sub
If CommonDialog2.Flags = 1024 Then

Label3.Caption = "Saving"
DoEvents
ProgressBar1.Value = 10
ReDim newbytes(1 To file_length)
For i = 1 To file_length
Data = 0
For j = 0 To 7
Data = Data + E(j, i) * 2 ^ j
Next j
bytes(i) = Data
If i = file_length / 4 Then ProgressBar1.Value = 25
If i = file_length / 2 Then ProgressBar1.Value = 40
Next i
ProgressBar1.Value = 55
For i = 0 To file_length - 1
Address = 0
For j = 0 To 18
Address = Address + B(j, i) * 2 ^ j
Next j
newbytes(Address + 1) = bytes(i + 1)
If i = file_length / 4 Then ProgressBar1.Value = 70
If i = file_length / 2 Then ProgressBar1.Value = 85
Next i
ProgressBar1.Value = 100
Label3.Caption = ""

Dim file_name2 As String
Dim fnum2 As Long
    file_name2 = CommonDialog2.FileName
    fnum2 = FreeFile
    Open file_name2 For Binary As #fnum2
    Put #fnum2, 1, newbytes
    Close fnum2

End If

End Sub


