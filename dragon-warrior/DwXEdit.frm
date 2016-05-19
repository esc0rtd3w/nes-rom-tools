VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "Comdlg32.ocx"
Begin VB.Form MapEditor 
   Caption         =   "DWxEdit"
   ClientHeight    =   6450
   ClientLeft      =   165
   ClientTop       =   345
   ClientWidth     =   9375
   LinkTopic       =   "Form1"
   ScaleHeight     =   430
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   625
   Begin VB.PictureBox Dw1Tiles 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   240
      Left            =   120
      Picture         =   "DwXEdit.frx":0000
      ScaleHeight     =   16
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   768
      TabIndex        =   25
      TabStop         =   0   'False
      Top             =   5400
      Visible         =   0   'False
      Width           =   11520
   End
   Begin VB.PictureBox Dw2Tiles 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   240
      Left            =   120
      Picture         =   "DwXEdit.frx":9042
      ScaleHeight     =   16
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   768
      TabIndex        =   23
      TabStop         =   0   'False
      Top             =   5640
      Visible         =   0   'False
      Width           =   11520
   End
   Begin VB.PictureBox Dw4Tiles 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   240
      Left            =   120
      Picture         =   "DwXEdit.frx":12084
      ScaleHeight     =   16
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   768
      TabIndex        =   22
      TabStop         =   0   'False
      Top             =   6120
      Visible         =   0   'False
      Width           =   11520
   End
   Begin MSComDlg.CommonDialog cmd 
      Left            =   6000
      Top             =   1920
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DefaultExt      =   "nes"
      Filter          =   "NES Files (*.nes)|*.nes"
   End
   Begin VB.PictureBox tsetHolder 
      AutoRedraw      =   -1  'True
      BackColor       =   &H000000FF&
      FontTransparent =   0   'False
      Height          =   780
      Left            =   0
      ScaleHeight     =   48
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   256
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   300
      Width           =   3900
      Begin VB.PictureBox pTileset 
         AutoRedraw      =   -1  'True
         BackColor       =   &H000000C0&
         BorderStyle     =   0  'None
         Height          =   240
         Left            =   0
         ScaleHeight     =   16
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   256
         TabIndex        =   6
         TabStop         =   0   'False
         Top             =   0
         Width           =   3840
         Begin VB.Shape sel1 
            BorderColor     =   &H0000FFFF&
            BorderStyle     =   6  'Inside Solid
            BorderWidth     =   2
            DrawMode        =   6  'Mask Pen Not
            Height          =   240
            Left            =   0
            Top             =   0
            Width           =   240
         End
         Begin VB.Shape PalBox 
            BorderStyle     =   6  'Inside Solid
            BorderWidth     =   2
            DrawMode        =   6  'Mask Pen Not
            Height          =   240
            Left            =   -240
            Top             =   0
            Width           =   240
         End
      End
   End
   Begin VB.PictureBox picToolbar 
      BorderStyle     =   0  'None
      Height          =   300
      Left            =   0
      ScaleHeight     =   20
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   625
      TabIndex        =   9
      TabStop         =   0   'False
      Top             =   0
      Width           =   9375
      Begin VB.CommandButton cmdMode 
         Caption         =   "M"
         BeginProperty Font 
            Name            =   "Small Fonts"
            Size            =   7.5
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Left            =   3600
         Style           =   1  'Graphical
         TabIndex        =   24
         Top             =   0
         Width           =   360
      End
      Begin VB.CommandButton cmdOpen 
         Height          =   300
         Left            =   6720
         Picture         =   "DwXEdit.frx":1B0C6
         Style           =   1  'Graphical
         TabIndex        =   19
         Top             =   0
         Width           =   375
      End
      Begin VB.CommandButton cmdNext 
         Caption         =   "-&>"
         Height          =   300
         Left            =   9000
         TabIndex        =   12
         Top             =   0
         Width           =   360
      End
      Begin VB.CommandButton cmdReload 
         Caption         =   "[&R]"
         Height          =   300
         Left            =   8640
         TabIndex        =   13
         Top             =   0
         Width           =   360
      End
      Begin VB.CommandButton cmdBack 
         Caption         =   "&<-"
         Height          =   300
         Left            =   8280
         TabIndex        =   11
         Top             =   0
         Width           =   360
      End
      Begin VB.TextBox txtFileName 
         Height          =   285
         Left            =   3960
         TabIndex        =   18
         Text            =   "C:\nes\dw3hack.nes"
         Top             =   0
         Width           =   2760
      End
      Begin VB.CommandButton cmdSaveNow 
         Caption         =   "&Save now!"
         Height          =   300
         Left            =   7200
         TabIndex        =   17
         Top             =   0
         Width           =   1080
      End
      Begin VB.CommandButton cmdZoom 
         Caption         =   "&Zoom"
         Height          =   300
         Left            =   960
         Style           =   1  'Graphical
         TabIndex        =   10
         Tag             =   "0"
         Top             =   0
         Width           =   960
      End
      Begin VB.Label lblSize 
         AutoSize        =   -1  'True
         Caption         =   "Size: 0/0"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   1920
         TabIndex        =   20
         Top             =   0
         Width           =   900
      End
      Begin VB.Label lblXY 
         AutoSize        =   -1  'True
         Caption         =   "X:0 Y:0"
         Height          =   195
         Left            =   0
         TabIndex        =   16
         Top             =   0
         Width           =   525
      End
   End
   Begin VB.PictureBox ActiveTileSet 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   240
      Left            =   120
      Picture         =   "DwXEdit.frx":1B210
      ScaleHeight     =   16
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   768
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   5160
      Visible         =   0   'False
      Width           =   11520
   End
   Begin VB.PictureBox Holder 
      BackColor       =   &H8000000C&
      BorderStyle     =   0  'None
      Height          =   2055
      Left            =   0
      ScaleHeight     =   137
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   241
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   2400
      Width           =   3615
      Begin VB.PictureBox Mapp 
         AutoRedraw      =   -1  'True
         BorderStyle     =   0  'None
         Height          =   3840
         Left            =   0
         ScaleHeight     =   256
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   256
         TabIndex        =   7
         Top             =   0
         Width           =   3840
         Begin VB.Shape MapCursor 
            BorderColor     =   &H00FFFFFF&
            BorderStyle     =   6  'Inside Solid
            BorderWidth     =   2
            DrawMode        =   6  'Mask Pen Not
            Height          =   240
            Left            =   0
            Top             =   0
            Width           =   240
         End
      End
   End
   Begin VB.HScrollBar TileScroller 
      Height          =   240
      LargeChange     =   128
      Left            =   0
      Max             =   512
      SmallChange     =   32
      TabIndex        =   4
      Top             =   1920
      Width           =   3615
   End
   Begin VB.PictureBox Dw3Tiles 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   240
      Left            =   120
      Picture         =   "DwXEdit.frx":24252
      ScaleHeight     =   16
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   768
      TabIndex        =   21
      TabStop         =   0   'False
      Top             =   5880
      Visible         =   0   'False
      Width           =   11520
   End
   Begin VB.VScrollBar VScroll 
      Height          =   2175
      LargeChange     =   16
      Left            =   4200
      Max             =   200
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   2280
      Width           =   240
   End
   Begin VB.HScrollBar HScroll 
      Height          =   240
      LargeChange     =   16
      Left            =   120
      Max             =   200
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   4800
      Width           =   3255
   End
   Begin VB.TextBox Resizer 
      BorderStyle     =   0  'None
      Height          =   255
      Left            =   4200
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   4920
      Width           =   255
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "Width:"
      Height          =   195
      Left            =   0
      TabIndex        =   15
      Top             =   0
      Width           =   465
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Width:"
      Height          =   195
      Left            =   0
      TabIndex        =   14
      Top             =   0
      Width           =   465
   End
   Begin VB.Menu mnuPop 
      Caption         =   "&Pop Up Menu"
      Visible         =   0   'False
      Begin VB.Menu mnuProps0 
         Caption         =   "Teleporter 0, (0,0) at 01-Overworld"
      End
      Begin VB.Menu mnuProps 
         Caption         =   "Properties"
         Visible         =   0   'False
         Begin VB.Menu mnuProps1 
            Caption         =   "Teleporter #0"
         End
         Begin VB.Menu mnuProps2 
            Caption         =   "(0,0) on 01 - Overworld"
         End
         Begin VB.Menu mnuProps3 
            Caption         =   "Goes to (0,0) on 00 - Fake Midenhall"
         End
      End
      Begin VB.Menu mnuSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPlace 
         Caption         =   "&Place Here"
      End
      Begin VB.Menu mnuRelocate 
         Caption         =   "&Throw to different map..."
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuSep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuStairs 
         Caption         =   "Not &Stairs"
      End
   End
End
Attribute VB_Name = "MapEditor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

DefLng A-Z

Const xMaxMapSize = 256, yMaxMapSize = 256
Dim xMapSize, yMapSize
Dim map(xMaxMapSize, yMaxMapSize) As Byte
Dim DispMap(xMaxMapSize, yMaxMapSize) As Byte
Dim PointerTableOffset, RomOffset
Dim PointerTable(512)

Private Type ObjType
  M As Long
  X As Long
  Y As Long
End Type

Const MaxObj = 1024

Dim sXpos, sYpos

Dim Obj(MaxObj) As ObjType

Const tHeight = 1
Dim NumTiles

Dim MapSize, CurMapSize

Dim EditMode
Dim MapNumber

Dim NumObj
Dim SelectedObj
Dim MinObjList

'Dim xSpriteSize, ySpriteSize
Dim xTileSize, yTileSize, xStart, yStart, xEnd, yEnd
Dim xBrushSize, yBrushSize, Brush(xMaxMapSize, yMaxMapSize) As Byte

Dim optBrushSize
Dim ZoomFactor As Single

Dim CameraX, CameraY
Dim WindowX, WindowY
Dim OldWindowX, OldWindowY

Function Hex2$(ByVal value)
Dim T$

T$ = Hex$(value)
If (Len(T$) \ 2) * 2 <> Len(T$) Then T$ = "0" + T$
Hex2$ = T$

End Function

Sub SaveMap()
  Dim Buffer As String, X, Y, Z, L, T, Offset, AddThis, S, Buffer2 As String
  Dim FileName As String
  FileName = txtFileName.Text
  If FileName = "" Then Exit Sub
  
  On Error GoTo SaveError
  
  CountSize
  If CurMapSize > MapSize Then
    MsgBox "The map is too big!  Reduce the size before saving!"
    Exit Sub
  End If
  
  Select Case WhichGame
    Case 2
      Select Case MapNumber
        Case 0
          PointerTableOffset = &H1D95& + &HC010&
          AddThis = &H9F97&
          Offset = AddThis - &H8000& + &HC0C10
          PointerTableOffset = &HDDA5&
          xMapSize = 255
          yMapSize = 255
          MapSize = 6496
        Case Else
          Exit Sub
      End Select
    Case 3
      Select Case MapNumber
        Case 0
          PointerTableOffset = &H18& + &H14010
          AddThis = &H821A&
          Offset = AddThis - &H8000& + &H14010
          xMapSize = 255
          yMapSize = 255
          MapSize = 6267
        Case 1
          PointerTableOffset = &H1A95 + &H14010
          AddThis = &H9BAB&
          Offset = AddThis - &H8000& + &H14010
          xMapSize = 157
          yMapSize = 137
          MapSize = 2116
        Case Else
          Exit Sub
      End Select
    Case 4
      Select Case MapNumber
        Case 0
          PointerTableOffset = &H2590& + &H2C010
          AddThis = &H8CEE&
          Offset = AddThis + &H2C010 - &H8000&
          xMapSize = 255
          yMapSize = 255
          MapSize = 6306
        Case 1
          PointerTableOffset = &H2B65& + &H2C010
          AddThis = &HA990&
          Offset = AddThis + &H2C010 - &H8000&
          xMapSize = 63
          yMapSize = 63
          MapSize = 469
        Case 2
          PointerTableOffset = &H2E89& + &H2C010
          AddThis = &HAC65&
          Offset = AddThis + &H2C010 - &H8000&
          xMapSize = 61
          yMapSize = 53
          MapSize = 548
        Case Else
          Exit Sub
      End Select
  End Select
  
  
  Select Case WhichGame
    Case 2
      X = 0: Y = 0: S = 0: T = -1
      PointerTable(0) = AddThis
      Do
        Z = map(X, Y)
        If T <> Z Then
          If T <> -1 Then Buffer = Buffer + Chr(32 * (T + 1) + L): S = S + 1
          T = Z
          L = 0
        Else
          L = L + 1
          If L = 31 Then
            Buffer = Buffer + Chr(32 * (T + 1) + L): S = S + 1
            T = -1
          End If
        End If
        If Z > 6 Then
          T = -1
          If Z = 7 Then Z = 0
          Buffer = Buffer + Chr(Z): S = S + 1
        End If
        
        If X = xMapSize Then
          X = -1
          Y = Y + 1
          If T <> -1 Then
            Buffer = Buffer + Chr(32 * (T + 1) + L): S = S + 1
            T = -1
          End If
          If Y > yMapSize Then Exit Do
          PointerTable(Y) = AddThis + S
        End If
        X = X + 1
      Loop
    Case 3
      X = 0: Y = 0: S = 0: T = -1
      PointerTable(0) = AddThis
      Do
        Z = map(X, Y)
        If T <> Z Then
          If T <> -1 Then Buffer = Buffer + Chr(32 * T + L): S = S + 1
          T = Z
          L = 0
        Else
          L = L + 1
          If (L = 31) Or (L = 7 And T = 7) Then
            Buffer = Buffer + Chr(32 * T + L): S = S + 1
            T = -1
          End If
        End If
        If Z > 7 Then
          T = -1
          Buffer = Buffer + Chr(&HE0 + Z): S = S + 1
        End If
        
        If X = xMapSize Then
          X = -1
          Y = Y + 1
          If T <> -1 Then
            Buffer = Buffer + Chr(32 * T + L): S = S + 1
            T = -1
          End If
          If Y > yMapSize Then Exit Do
          PointerTable(Y) = AddThis + S
        End If
        X = X + 1
      Loop
    Case 4
      X = 0: Y = 0: S = 0: T = -1
      PointerTable(0) = AddThis
      Do
        Z = map(X, Y)
        If T <> Z Then
          If T <> -1 Then Buffer = Buffer + Chr(32 * T + L): S = S + 1
          T = Z
          L = 0
        Else
          L = L + 1
          If (L = 31) Or (L = 7 And T = 7) Then
            Buffer = Buffer + Chr(32 * T + L): S = S + 1
            T = -1
          End If
        End If
        If Z > 7 Then
          T = -1
          Buffer = Buffer + Chr(&HE0 + Z): S = S + 1
        End If
        If X = 127 Then
          If T <> -1 Then
            Buffer = Buffer + Chr(32 * T + L): S = S + 1
            T = -1
          End If
          PointerTable(Y * 2 + 1) = (S - (PointerTable(Y * 2) - AddThis))
        End If
        If X = xMapSize Then
          If T <> -1 Then
            Buffer = Buffer + Chr(32 * T + L): S = S + 1
            T = -1
          End If
          If X >= 127 Then
            PointerTable(Y * 2 + 1) = (S - (PointerTable(Y * 2) - AddThis)) * 256 + PointerTable(Y * 2 + 1)
          Else
            PointerTable(Y * 2 + 1) = (S - (PointerTable(Y * 2) - AddThis)) * 256 + (S - (PointerTable(Y * 2) - AddThis))
          End If
          X = -1
          Y = Y + 1
          If Y > yMapSize Then Exit Do
          PointerTable(Y * 2) = AddThis + S
        End If
        X = X + 1
      Loop
    Case Else
  End Select

  
  
  Select Case WhichGame
    Case 2
      If FileLen(FileName) < 204303 Then
        MsgBox "Target file is too small to be Dragon Warrior 2!"
        Exit Sub
      End If
      Buffer2 = ""
      For Y = 0 To yMapSize
        Buffer2 = Buffer2 + Chr(PointerTable(Y) And 255)
        Buffer2 = Buffer2 + Chr(PointerTable(Y) \ 256)
      Next
      Open FileName For Binary As #1
        Put #1, Offset + 1, Buffer
        Put #1, PointerTableOffset + 1, Buffer2
      Close
      Buffer = ""
      For X = 0 To NumObj
        Buffer = Buffer + Chr(Obj(X).M)
        Buffer = Buffer + Chr(Obj(X).X)
        Buffer = Buffer + Chr(Obj(X).Y)
      Next
      Open FileName For Binary As #1
        Put #1, &HA279& + 1, Buffer
      Close
    Case 3
      If FileLen(FileName) < 524303 Then
        MsgBox "Target file is too small to be Dragon Warrior 3!"
        Exit Sub
      End If
      Buffer2 = ""
      For Y = 0 To yMapSize
        Buffer2 = Buffer2 + Chr(PointerTable(Y) And 255)
        Buffer2 = Buffer2 + Chr(PointerTable(Y) \ 256)
      Next
      Open FileName For Binary As #1
        Put #1, Offset + 1, Buffer
        Put #1, PointerTableOffset + 1, Buffer2
      Close
    Case 4
      If FileLen(FileName) < 524303 Then
        MsgBox "Target file is too small to be Dragon Warrior 4!"
        Exit Sub
      End If
      Buffer2 = ""
      X = yMapSize * 2
      For Y = 0 To X
        Buffer2 = Buffer2 + Chr(PointerTable(Y) And 255)
        Buffer2 = Buffer2 + Chr(PointerTable(Y) \ 256)
      Next
      Open FileName For Binary As #1
        Put #1, Offset + 1, Buffer
        Put #1, PointerTableOffset + 1, Buffer2
      Close
    Case Else
      Exit Sub
  End Select
  
  Exit Sub
SaveError:
  MsgBox "Error " + Error + " occurred when saving " + FileName
  Close
  Exit Sub
End Sub

Sub LoadMap()
  Dim FileName As String, Buffer As String, Pos, GetByte, X, Y, L, T, Q, Offset
  'On Error GoTo LoadError
  FileName = txtFileName
  If FileName = "" Then Exit Sub
  If FileLen(FileName) < 12800 Then
    MsgBox "The File is too small to be a Dragon Warrior game!"
    Exit Sub
  End If
  Buffer = Space(16)
  Offset = &H3FF0
  Open FileName For Binary As #1
    Get #1, Offset + 1, Buffer
  Close
  Select Case Buffer
    Case "DRAGON WARRIOR  ": WhichGame = 1
    Case "DRAGON WARRIORS2": WhichGame = 2
    Case "DRAGON WARRIOR 3": WhichGame = 3
    Case " DRAGON QUEST IV": WhichGame = 4
  End Select
  
  For Y = 0 To yMaxMapSize
  For X = 0 To xMaxMapSize
    map(X, Y) = 0
    DispMap(X, Y) = 0
  Next
  Next
  
  Select Case WhichGame
    Case 1
'      Buffer = Space(256 * 3)
'      Open FileName For Binary As #1
'        Get #1, &HA279& + 1, Buffer
'      Close
'      NumObj = 255
'      For X = 0 To 255
'        Obj(X).M = Asc(Mid(Buffer, X * 3 + 1, 1))
'        Obj(X).X = Asc(Mid(Buffer, X * 3 + 2, 1))
'        Obj(X).Y = Asc(Mid(Buffer, X * 3 + 3, 1))
'      Next
'      Open FileName For Binary As #1
'        Get #1, &HFD0E& + 1, Buffer
'      Close
'      NumObj = 511
'      For X = 0 To 255
'        Obj(X + 256).M = Asc(Mid(Buffer, X * 3 + 1, 1))
'        Obj(X + 256).X = Asc(Mid(Buffer, X * 3 + 2, 1))
'        Obj(X + 256).Y = Asc(Mid(Buffer, X * 3 + 3, 1))
'      Next
      
      
      Offset = &H10&
      Select Case MapNumber
        Case 0
'          Offset = &HDFA7&
          PointerTableOffset = &H2653
          xMapSize = 119
          yMapSize = 119
          MapSize = 2294
        Case Else
          Exit Sub
      End Select
    
    Case 2
      Buffer = Space(256 * 3)
      Open FileName For Binary As #1
        Get #1, &HA279& + 1, Buffer
      Close
      NumObj = 255
      For X = 0 To 255
        Obj(X).M = Asc(Mid(Buffer, X * 3 + 1, 1))
        Obj(X).X = Asc(Mid(Buffer, X * 3 + 2, 1))
        Obj(X).Y = Asc(Mid(Buffer, X * 3 + 3, 1))
      Next
      Open FileName For Binary As #1
        Get #1, &HFD0E& + 1, Buffer
      Close
      NumObj = 511
      For X = 0 To 255
        Obj(X + 256).M = Asc(Mid(Buffer, X * 3 + 1, 1))
        Obj(X + 256).X = Asc(Mid(Buffer, X * 3 + 2, 1))
        Obj(X + 256).Y = Asc(Mid(Buffer, X * 3 + 3, 1))
      Next
      
      
      Offset = &HC010&
      Select Case MapNumber
        Case 0
'          Offset = &HDFA7&
          PointerTableOffset = &H1D95
          xMapSize = 255
          yMapSize = 255
          MapSize = 6496
        Case Else
          Exit Sub
      End Select
    Case 3
      Offset = &H14010
      Select Case MapNumber
        Case 0
          PointerTableOffset = &H18&
          xMapSize = 255
          yMapSize = 255
          MapSize = 6267
        Case 1
          PointerTableOffset = &H1A95&
          xMapSize = 157
          yMapSize = 137
          MapSize = 2116
        Case Else
          Exit Sub
      End Select
    Case 4
      Offset = &H2C010
      Select Case MapNumber
        Case 0
          PointerTableOffset = &H2590&
          xMapSize = 255
          yMapSize = 255
          MapSize = 6306
        Case 1
          PointerTableOffset = &H2B65&
          xMapSize = 63
          yMapSize = 63
          MapSize = 469
        Case 2
          PointerTableOffset = &H2E89&
          xMapSize = 61
          yMapSize = 53
          MapSize = 548
        Case Else
          Exit Sub
      End Select
  End Select
  
  Buffer = Space(16384)
  Open FileName For Binary As #1
    Get #1, Offset + 1, Buffer
  Close
 X = 0: Y = 0
 'pos=0
'  If WhichGame = 4 Then MapSize = 0
  Select Case WhichGame
    Case 1
      For Y = 0 To yMapSize
        Pos = Asc(Mid(Buffer, PointerTableOffset + Y * 2 + 1, 1)) + Asc(Mid(Buffer, PointerTableOffset + Y * 2 + 2, 1)) * 256&
        Pos = Pos - &H8000&
        X = 0
        Do
          Pos = Pos + 1
          GetByte = Asc(Mid(Buffer, Pos, 1))
          L = GetByte And 15
          T = GetByte \ 16
          For Q = 0 To L
            map(X, Y) = T
            X = X + 1
            If X > xMapSize Then Exit Do
          Next
        Loop
      Next
    Case 2
      
      For Y = 0 To yMapSize
        Pos = Asc(Mid(Buffer, PointerTableOffset + Y * 2 + 1, 1)) + Asc(Mid(Buffer, PointerTableOffset + Y * 2 + 2, 1)) * 256&
        Pos = Pos - &H8000&
        X = 0
        Do
          Pos = Pos + 1
          GetByte = Asc(Mid(Buffer, Pos, 1))
          L = GetByte And 31
          T = GetByte \ 32 - 1
          If GetByte < 32 Then
            T = GetByte
            L = 0
          End If
          If GetByte = 0 Then
            T = 7
          End If
          For Q = 0 To L
            map(X, Y) = T
            X = X + 1
            If X > xMapSize Then Exit Do
          Next
        Loop
      Next
'      Do
'        Pos = Pos + 1
'        GetByte = Asc(Mid(Buffer, Pos, 1))
'        L = GetByte And 31
'        T = GetByte \ 32 - 1
'        If GetByte < 32 Then
'          T = (GetByte And 31) + 7
'          L = 0
'        End If
'        For Q = 0 To L
'          map(X, Y) = T
'          X = X + 1
'          If X > xMapSize Then
'            X = 0
'            Y = Y + 1
'            If Y > yMapSize Then
'              Exit Do
'            End If
'          End If
'        Next
'      Loop
    Case 3
      For Y = 0 To yMapSize
        Pos = Asc(Mid(Buffer, PointerTableOffset + Y * 2 + 1, 1)) + Asc(Mid(Buffer, PointerTableOffset + Y * 2 + 2, 1)) * 256&
        Pos = Pos - &H8000&
        X = 0
        Do
          Pos = Pos + 1
          GetByte = Asc(Mid(Buffer, Pos, 1))
          L = GetByte And 31
          T = GetByte \ 32
          If GetByte >= &HE8 Then
            T = GetByte - &HE0
            L = 0
          End If
          For Q = 0 To L
            map(X, Y) = T
            X = X + 1
            If X > xMapSize Then Exit Do
          Next
        Loop
      Next
    Case 4
      For Y = 0 To yMapSize
        Pos = Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 1, 1)) + Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 2, 1)) * 256&
        Pos = Pos - &H8000&
        X = 0
        Do
          Pos = Pos + 1
          GetByte = Asc(Mid(Buffer, Pos, 1))
          L = GetByte And 31
          T = GetByte \ 32
          If GetByte >= &HE8 Then
            T = GetByte - &HE0
            L = 0
          End If
          For Q = 0 To L
            map(X, Y) = T
            X = X + 1
            If X = 128 Then
              Pos = Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 1, 1)) + Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 2, 1)) * 256& + Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 3, 1))
              Pos = Pos - &H8000&
              Exit For
            End If
            If X = 192 Then
'              Pos = Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 1, 1)) + Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 2, 1)) * 256& + Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 4, 1)) + 256 '+ Asc(Mid(Buffer, PointerTableOffset + Y * 4 + 3, 1))
'
'              Pos = Pos - &H8000&
'              Exit For
            End If
            If X > xMapSize Then Exit Do
          Next
        Loop
      Next
    Case Else
      Do
        Pos = Pos + 1
        GetByte = Asc(Mid(Buffer, Pos, 1))
        L = GetByte And 31
        T = GetByte \ 32
        If GetByte >= &HE8 Then
          T = GetByte - &HE0
          L = 0
        End If
        For Q = 0 To L
          map(X, Y) = T
          X = X + 1
          If X > xMapSize Then
            X = 0
            Y = Y + 1
            If Y > yMapSize Then
              Exit Do
            End If
          End If
        Next
      Loop
  End Select
  UpdateTileset
  CountSize
  SmoothMap 0, 0, xMapSize, yMapSize
  Mapp.Cls
  DrawMap CameraX, CameraY, xMapSize, yMapSize
  Form_Resize
  GetNames
Exit Sub
LoadError:
  MsgBox "Error " + Error + " occurred when loading " + FileName
  Close
End Sub

Sub CountSize()
  Dim X, Y, T, L, S, Z
  T = -1
  Select Case WhichGame
    Case 1
      Do
        Z = map(X, Y)
        If T <> Z Then
          If T <> -1 Then S = S + 1
          T = Z
          L = 0
        Else
          L = L + 1
          If L = 15 Then
            S = S + 1
            T = -1
          End If
        End If
        If X = xMapSize Then
          X = -1
          Y = Y + 1
          If T <> -1 Then
            S = S + 1
            T = -1
          End If
          If Y > yMapSize Then Exit Do
        End If
        X = X + 1
      Loop
    Case 2
      Do
        Z = map(X, Y)
        If T <> Z Then
          If T <> -1 Then S = S + 1
          T = Z
          L = 0
        Else
          L = L + 1
          If (L = 31) Or (L = 7 And T = 7) Then
            S = S + 1
            T = -1
          End If
        End If
        If Z > 6 Then
          T = -1
          S = S + 1
        End If
        If X = xMapSize Then
          X = -1
          Y = Y + 1
          If T <> -1 Then
            S = S + 1
            T = -1
          End If
          If Y > yMapSize Then Exit Do
        End If
        X = X + 1
      Loop
    Case 3
      Do
        Z = map(X, Y)
        If T <> Z Then
          If T <> -1 Then S = S + 1
          T = Z
          L = 0
        Else
          L = L + 1
          If (L = 31) Or (L = 7 And T = 7) Then
            S = S + 1
            T = -1
          End If
        End If
        If Z > 7 Then
          T = -1
          S = S + 1
        End If
    
        If X = xMapSize Then
          X = -1
          Y = Y + 1
          If T <> -1 Then
            S = S + 1
            T = -1
          End If
          If Y > yMapSize Then Exit Do
        End If
        X = X + 1
      Loop
    Case 4
      Do
        Z = map(X, Y)
        If T <> Z Then
          If T <> -1 Then S = S + 1
          T = Z
          L = 0
        Else
          L = L + 1
          If (L = 31) Or (L = 7 And T = 7) Then
            S = S + 1
            T = -1
          End If
        End If
        If Z > 7 Then
          T = -1
          S = S + 1
        End If
        If X = 127 Or X = xMapSize Then
          If T <> -1 Then
            S = S + 1
            T = -1
          End If
        End If
        If X = xMapSize Then
          X = -1
          Y = Y + 1
          If Y > yMapSize Then Exit Do
        End If
        X = X + 1
      Loop
    Case Else
      Exit Sub
  End Select
  CurMapSize = S
  lblSize.Caption = "Size: " + Trim(Str(CurMapSize)) + "/" + Trim(Str(MapSize))
  lblSize.ForeColor = vbWindowText
  If CurMapSize > MapSize Then lblSize.ForeColor = QBColor(12)

End Sub


Sub SmoothMap(x1, y1, x2, y2)
  Dim X, Y, Z, Q, B
  Dim T1, T2, T3, T4, T5, T6, T7, T8
  
  Randomize
  
  If x1 < 0 Then x1 = 0
  If x2 > xMapSize Then x2 = xMapSize
  If y1 < 0 Then y1 = 0
  If y2 > yMapSize Then y2 = yMapSize
  
  For X = x1 To x2
    For Y = y1 To y2
      Z = map(X, Y)
      If Z = 4 And WhichGame = 1 Then
        Z = 16
        If X > 0 Then
          If map(X - 1, Y) <> 4 And map(X - 1, Y) <> 11 Then Z = Z Or 2
        End If
        If X < xMapSize Then
          If map(X + 1, Y) <> 4 And map(X + 1, Y) <> 11 Then Z = Z Or 1
        End If
        If Y > 0 Then
          If map(X, Y - 1) <> 4 And map(X, Y - 1) <> 11 Then Z = Z Or 4
        End If
        If Y < yMapSize Then
          If map(X, Y + 1) <> 4 And map(X, Y + 1) <> 11 Then Z = Z Or 8
        End If
        If Z = 16 Then Z = 4

      End If
      
      If Z = 3 And WhichGame = 2 Then
        'Okay, this gets complicated.  T1-T8 are the 8 tiles around a tile.
        '536
        '2 1
        '748
        'These are set to 3 if it's water or bridges

        Z = 32
        T1 = 3: T2 = 3: T3 = 3: T4 = 3: T5 = 3: T6 = 3: T7 = 3: T8 = 3
           
        If X < xMapSize Then T1 = map(X + 1, Y)
        If X > 0 Then T2 = map(X - 1, Y)
        If Y > 0 Then T3 = map(X, Y - 1)
        If Y < yMapSize Then T4 = map(X, Y + 1)
            
        If T1 = 3 Or T1 = 9 Or T1 = 13 Then T1 = 3
        If T2 = 3 Or T2 = 9 Or T2 = 13 Then T2 = 3
        If T3 = 3 Or T3 = 9 Or T3 = 13 Then T3 = 3
        If T4 = 3 Or T4 = 9 Or T4 = 13 Then T4 = 3
            
        If T1 <> 3 Then Z = Z Or 1
        If T2 <> 3 Then Z = Z Or 2
        If T3 <> 3 Then Z = Z Or 4
        If T4 <> 3 Then Z = Z Or 8
            
        If Z <> 32 Then
          If X > 0 And Y > 0 Then T5 = map(X - 1, Y - 1)
          If X < xMapSize And Y > 0 Then T6 = map(X + 1, Y - 1)
          If X > 0 And Y < yMapSize Then T7 = map(X - 1, Y + 1)
          If X < xMapSize And Y < yMapSize Then T8 = map(X + 1, Y + 1)
            
          If T5 = 3 Or T5 = 9 Or T5 = 13 Then T5 = 3
          If T6 = 3 Or T6 = 9 Or T6 = 13 Then T6 = 3
          If T7 = 3 Or T7 = 9 Or T7 = 13 Then T7 = 3
          If T8 = 3 Or T8 = 9 Or T8 = 13 Then T8 = 3

          If Z = 32 + 1 + 4 And T7 <> 3 Then Z = 32
          If Z = 32 + 1 + 8 And T5 <> 3 Then Z = 32
          If Z = 32 + 2 + 4 And T8 <> 3 Then Z = 32
          If Z = 32 + 2 + 8 And T6 <> 3 Then Z = 32
          If Z = 32 + 4 And T4 = 3 And T8 <> 3 Then Z = 32
          If Z = 32 + 8 And T3 = 3 And T5 <> 3 Then Z = 32
          If Z = 32 + 1 And T2 = 3 And T7 <> 3 Then Z = 32
          If Z = 32 + 2 And T1 = 3 And T6 <> 3 Then Z = 32
            
        End If
        If Z = 32 Then Z = 3
      End If
      If Z = 0 And WhichGame = 3 Then
        Z = 32
        If X > 0 Then
          If map(X - 1, Y) <> 0 And map(X - 1, Y) < 23 Then Z = Z Or 2
        End If
        If X < xMapSize Then
          If map(X + 1, Y) <> 0 And map(X + 1, Y) < 23 Then Z = Z Or 1
        End If
        If Y > 0 Then
          If map(X, Y - 1) <> 0 And map(X, Y - 1) < 23 Then Z = Z Or 4
        End If
        If Y < yMapSize Then
          If map(X, Y + 1) <> 0 And map(X, Y + 1) < 23 Then Z = Z Or 8
        End If
        If Z = 32 Then Z = 0
      End If
      If Z = 0 And WhichGame = 4 Then
        Z = 32
        If X > 0 Then
          If map(X - 1, Y) <> 0 And map(X - 1, Y) <> 10 And map(X - 1, Y) <> 22 Then Z = Z Or 2
        End If
        If X < xMapSize Then
          If map(X + 1, Y) <> 0 And map(X + 1, Y) <> 10 And map(X + 1, Y) <> 22 Then Z = Z Or 1
        End If
        If Y > 0 Then
          If map(X, Y - 1) <> 0 And map(X, Y - 1) <> 10 And map(X, Y - 1) <> 22 Then Z = Z Or 4
        End If
        If Y < yMapSize Then
          If map(X, Y + 1) <> 0 And map(X, Y + 1) <> 10 And map(X, Y + 1) <> 22 Then Z = Z Or 8
        End If
        If Z = 32 Then Z = 0
      End If
      If MapNumber = 0 And WhichGame = 3 Then
       If Z = 1 Then
        If Y < 100 Then Z = 32
        If Y > 229 Then Z = 32
       End If
      End If
      If MapNumber = 2 And WhichGame = 4 Then
       If Z = 1 Then
         Z = 24
         If Int(Rnd * 50) = 0 Then Z = 25
         DispMap(X, Y) = Z
       End If
      End If
        
      DispMap(X, Y) = Z
    Next
  Next
End Sub


Sub SwapIfLess(ByRef num1, ByRef num2)
  Dim num3
  If num1 < num2 Then
    num3 = num1
    num1 = num2
    num2 = num3
  End If
End Sub


Sub Start()
  txtFileName.Text = GetSetting("DW3OVEDIT", "Files", "Filename", "")
  SelectedObj = -1
  ZoomFactor = 1
  xStart = -1
  xTileSize = 16
  yTileSize = 16
  xBrushSize = 0
  yBrushSize = 0
'  xSpriteSize = 16
'  ySpriteSize = 16
  xMapSize = 255: yMapSize = 255
  NumObj = -1
  MapNames(1) = "Overworld"
  LoadMap
  MsgBox "This is an alpha version, so please report all bugs!"
End Sub

Sub DrawTile(X, Y)
  Dim T, Z, x1, y1, x2, y2
  If X < CameraX Or X > CameraX + WindowX Or Y < CameraY Or Y > CameraY + WindowY Then Exit Sub
  With Mapp
    x1 = X - CameraX
    y1 = Y - CameraY
    T = DispMap(X, Y)
    Z = BitBlt(.hDC, x1 * xTileSize, y1 * yTileSize, xTileSize, yTileSize, ActiveTileSet.hDC, T * xTileSize, 0, SRCCOPY)
  End With
End Sub

Sub DrawMap(ByVal xx1, ByVal yy1, ByVal xx2, ByVal yy2)
  Dim X, Y, T, Z
  Dim x1, y1, x2, y2
  If xx1 < CameraX Then xx1 = CameraX
  If xx2 > CameraX + WindowX Then xx2 = CameraX + WindowX
  If xx2 < xx1 Then Exit Sub
  If yy1 < CameraY Then yy1 = CameraY
  If yy2 > CameraY + WindowY Then yy2 = CameraY + WindowY
  If yy2 < yy1 Then Exit Sub
  
  With Mapp
    For X = xx1 To xx2
    For Y = yy1 To yy2
      x1 = X - CameraX
      y1 = Y - CameraY
      T = DispMap(X, Y)
      Z = BitBlt(.hDC, x1 * xTileSize, y1 * yTileSize, xTileSize, yTileSize, ActiveTileSet.hDC, T * xTileSize, 0, SRCCOPY)
    Next
    Next
  End With
  'Mapp.Refresh
  DrawObjects xx1, yy1, xx2, yy2
End Sub

Sub DrawObjects(ByVal xx1, ByVal yy1, ByVal xx2, ByVal yy2)
  Dim I, x1, y1, x2, y2, X, Y, M
  For I = 0 To NumObj
    X = Obj(I).X
    Y = Obj(I).Y
    M = Obj(I).M And 127
    If X >= xx1 And X <= xx2 And Y >= yy1 And Y <= yy2 And M = 1 Then
      x1 = (X - CameraX) * xTileSize
      y1 = (Y - CameraY) * yTileSize
      x2 = x1 + xTileSize - 1
      y2 = y1 + yTileSize - 1
      Mapp.Line (x1, y1)-(x2, y2), RGB(255, 200, 64), B
      Mapp.Line (x1 + 1, y1 + 1)-(x2 - 1, y2 - 1), RGB(255, 200, 64), B
    End If
  Next
  Mapp.Refresh
'  Dim x, y, z, i
'  Dim x1, y1, w, h, x2, y2
'  With Mapp
'    For i = 0 To NumSprite + 1
'      x1 = Sprites(i).x * ZoomFactor * 4
'      y1 = Sprites(i).y * ZoomFactor * 4
'      w = xSpriteSize
'      h = ySpriteSize
'      x2 = xSpriteSize * Sprites(i).T
'      y2 = 0
'      If Sprites(i).f Then y2 = ySpriteSize * 2
'      z = BitBlt(.hDC, x1, y1, w, h, ActiveSpriteSet.hDC, x2, y2 + h, SRCAND)
'      z = BitBlt(.hDC, x1, y1, w, h, ActiveSpriteSet.hDC, x2, y2, SRCPAINT)
'    Next
'    .Refresh
'  End With
End Sub

Sub UpdateWorkspace()
'  Dim X, z
'  With Mapp
'    .Width = xTileSize * xMapSize
'    .Height = yTileSize * yMapSize
'  End With
'  DrawMap 0, 0, xMapSize, yMapSize
End Sub

Sub UpdateTileset()
  Dim X, Y, Z
  If WhichGame = 1 Then ActiveTileSet.PaintPicture Dw1Tiles.Picture, 0, 0, ActiveTileSet.Width, ActiveTileSet.Height, 0, 0, Dw1Tiles.Width, Dw3Tiles.Height, vbSrcCopy: NumTiles = 16
  If WhichGame = 2 Then ActiveTileSet.PaintPicture Dw2Tiles.Picture, 0, 0, ActiveTileSet.Width, ActiveTileSet.Height, 0, 0, Dw2Tiles.Width, Dw3Tiles.Height, vbSrcCopy: NumTiles = 20
  If WhichGame = 3 Then ActiveTileSet.PaintPicture Dw3Tiles.Picture, 0, 0, ActiveTileSet.Width, ActiveTileSet.Height, 0, 0, Dw3Tiles.Width, Dw3Tiles.Height, vbSrcCopy: NumTiles = 32
  If WhichGame = 4 Then ActiveTileSet.PaintPicture Dw4Tiles.Picture, 0, 0, ActiveTileSet.Width, ActiveTileSet.Height, 0, 0, Dw4Tiles.Width, Dw4Tiles.Height, vbSrcCopy: NumTiles = 32
  
  
  With pTileset
    .Width = xTileSize * NumTiles
    .Height = yTileSize
    For X = 0 To NumTiles
      Z = BitBlt(.hDC, X * xTileSize, 0 * yTileSize, xTileSize, yTileSize, ActiveTileSet.hDC, X * xTileSize, 0, SRCCOPY)
    Next
    .Refresh
  End With
End Sub

Private Sub cmdBack_Click()
  Dim Z
  If MapNumber = 0 Then Exit Sub
  Z = MsgBox("Save changes?", vbYesNoCancel)
  If Z = vbCancel Then Exit Sub
  If Z = vbYes Then SaveMap
  MapNumber = MapNumber - 1
  LoadMap
End Sub

Private Sub cmdMode_Click()
  EditMode = Not EditMode
  If EditMode = 0 Then
    cmdMode.BackColor = vbButtonFace
  Else
    cmdMode.BackColor = vb3DHighlight
  End If
  MapCursor.Height = yTileSize
  MapCursor.Width = xTileSize
  
End Sub

'Private Sub cmdBrushSize_Click(Index As Integer)
'  Dim i
'  For i = 0 To cmdBrushSize.Count - 1
'    cmdBrushSize(i).BackColor = &H8000000F
'  Next
'  cmdBrushSize(Index).BackColor = &H80000016
'  optBrushSize = Index
'End Sub

'Private Sub cmdMode_Click(Index As Integer)
'CmdMode(Index).BackColor = vb3DHighlight
'CmdMode(Index Xor 1).BackColor = vbButtonFace
'EditMode = Index
'If Index = 0 Then
'  MapCursor.Width = xTileSize
'  MapCursor.Height = yTileSize
'Else
'  MapCursor.Width = xSpriteSize
'  MapCursor.Height = ySpriteSize
'End If
'End Sub

Private Sub cmdNext_Click()
  Dim Z
  If WhichGame = 2 Then MapNumber = 0: Exit Sub
  If WhichGame = 3 And MapNumber = 1 Then Exit Sub
  If WhichGame = 4 And MapNumber = 2 Then Exit Sub
  Z = MsgBox("Save changes?", vbYesNoCancel)
  If Z = vbCancel Then Exit Sub
  If Z = vbYes Then SaveMap
  MapNumber = MapNumber + 1
  LoadMap
End Sub

Private Sub cmdOpen_Click()
  On Error GoTo OpenCancel
  cmd.ShowOpen
  txtFileName.Text = cmd.FileName
  
Exit Sub
OpenCancel:
  Exit Sub
End Sub

Private Sub cmdReload_Click()
  If MsgBox("Reload! Are you sure?", vbYesNo) = vbYes Then LoadMap
End Sub

Private Sub cmdSaveNow_Click()
  SaveMap
End Sub

Private Sub cmdZoom_Click()
  If cmdZoom.Tag = "" Then cmdZoom.Tag = 0
  cmdZoom.Tag = Not cmdZoom.Tag
  If cmdZoom.Tag Then
    ZoomFactor = 2
    cmdZoom.BackColor = &H80000016
    With ActiveTileSet
      xTileSize = xTileSize * 2
      yTileSize = yTileSize * 2
      .Width = .Width * 2
      .Height = .Height * 2
      UpdateTileset
'      .PaintPicture .Picture, 0, 0, .Width, .Height, , , .Width \ 2, .Height \ 2, vbSrcCopy
        sel1.Width = sel1.Width * 2
        sel1.Height = sel1.Height * 2
        MapCursor.Width = MapCursor.Width * 2
        MapCursor.Height = MapCursor.Height * 2
        MapCursor.Left = MapCursor.Left * 2
        MapCursor.Top = MapCursor.Top * 2
      .Refresh
    End With
'    With ActiveSpriteSet
'      xSpriteSize = xSpriteSize * 2
'      ySpriteSize = ySpriteSize * 2
'      .Width = .Width * 2
'      .Height = .Height * 2
'      .PaintPicture .Picture, 0, 0, .Width, .Height, , , .Width \ 2, .Height \ 2, vbSrcCopy
'      .Refresh
'    End With
    Me.WindowState = vbMaximized
  Else
    ZoomFactor = 1
    cmdZoom.BackColor = &H8000000F
    With ActiveTileSet
      xTileSize = xTileSize \ 2
      yTileSize = yTileSize \ 2
      .PaintPicture .Picture, 0, 0, .Width \ 2, .Height \ 2, , , , , vbSrcCopy
      .Width = .Width \ 2
      .Height = .Height \ 2
        sel1.Width = sel1.Width \ 2
        sel1.Height = sel1.Height \ 2
        MapCursor.Width = MapCursor.Width \ 2
        MapCursor.Height = MapCursor.Height \ 2
        MapCursor.Left = MapCursor.Left \ 2
        MapCursor.Top = MapCursor.Top \ 2
      .Refresh
    End With
'    With ActiveSpriteSet
'      xSpriteSize = xSpriteSize \ 2
'      ySpriteSize = ySpriteSize \ 2
'      .PaintPicture .Picture, 0, 0, .Width \ 2, .Height \ 2, , , , , vbSrcCopy
'      .Width = .Width \ 2
'      .Height = .Height \ 2
'      .Refresh
'    End With
    
    Me.WindowState = vbNormal
  End If
  UpdateTileset
  Form_Resize
End Sub


Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
  Dim X, Y
  X = HScroll.value
  Y = VScroll.value
  Select Case KeyCode
    Case vbKeyLeft
      X = X - 2
    Case vbKeyRight
      X = X + 2
    Case vbKeyUp
      Y = Y - 2
    Case vbKeyDown
      Y = Y + 2
  End Select
  
  If X > HScroll.Max Then
    HScroll.value = HScroll.Max
  ElseIf X < 0 Then
    HScroll.value = 0
  Else
    HScroll.value = X
  End If
    
  If Y > VScroll.Max Then
    VScroll.value = VScroll.Max
  ElseIf Y < 0 Then
    VScroll.value = 0
  Else
    VScroll.value = Y
  End If
    
End Sub

Private Sub Form_Load()
Start
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
  Select Case MsgBox("Save map?", vbYesNoCancel)
    Case vbYes
      SaveMap
    Case vbCancel
      Cancel = True
  End Select
  SaveSetting "DW3OVEDIT", "Files", "Filename", txtFileName.Text

End Sub

Private Sub Form_Resize()
Dim fHeight, fWidth
Dim Scrollval
Dim Toppy



fHeight = MapEditor.ScaleHeight: fWidth = MapEditor.ScaleWidth

On Error Resume Next

With tsetHolder
  .Left = 0
  .Width = fWidth
  .Height = pTileset.Height + 4
End With

With TileScroller
  .Left = 0
  .Width = fWidth
  .Top = tsetHolder.Height + tsetHolder.Top
  .Height = 16
  Scrollval = pTileset.Width - tsetHolder.ScaleWidth
  If Scrollval > 0 Then
    If .value > Scrollval Then .value = Scrollval
    .Max = Scrollval
    .Enabled = True
    .Visible = True
  Else
    If .value <> 0 Then .value = 0
    .Enabled = False
    .Visible = False
  End If
End With

With Resizer
  .Left = fWidth - 17
  .Top = fHeight - 17
End With

Toppy = TileScroller.Height + TileScroller.Top
If TileScroller.Visible = False Then Toppy = TileScroller.Top

With Holder
  .Left = 0
  .Top = Toppy
  .Width = fWidth - 16 - .Left
  .Height = fHeight - 16 - .Top
End With
Mapp.Width = Holder.Width ' - 2
Mapp.Height = Holder.Height ' - 2
OldWindowX = WindowX
OldWindowY = WindowY

WindowX = (Mapp.Width - xTileSize) \ xTileSize
WindowY = (Mapp.Height - xTileSize) \ yTileSize


'DrawMap CameraX, CameraY + WindowY + 1, CameraX + WindowX + 1, CameraY + WindowY + 1
'DrawMap CameraX + WindowX - 1, CameraY, CameraX + WindowX + 1, CameraY + WindowY + 1


If OldWindowX <> WindowX Or OldWindowY <> WindowY Then DrawMap 0, 0, xMapSize, yMapSize

With HScroll
  .Top = fHeight - 16
  .Left = Holder.Left
  .Width = fWidth - .Left - 16
  Scrollval = xMapSize - WindowX
'  if (mapp.Width-xtilesize+1)
  
  If Scrollval > 0 Then
    If .value > Scrollval Then .value = Scrollval
    .Max = Scrollval
    .Enabled = True
  Else
    CameraX = 0
    .value = 0
    .Max = 0
    .Enabled = False
  End If
End With

With VScroll
  .Top = Holder.Top
  .Left = fWidth - 16
  .Height = fHeight - .Top - 16
  Scrollval = yMapSize - WindowY
  If Scrollval > 0 Then
    If .value > Scrollval Then .value = Scrollval
    .Max = Scrollval
    .Enabled = True
  Else
    CameraY = 0
    .value = 0
    .Max = 0
    .Enabled = False
  End If
End With

If OldWindowX = WindowX And WindowY = OldWindowY Then
Else
  Mapp.Line ((WindowX + 1) * xTileSize, 0)-((WindowX + 300) * xTileSize, (WindowY + 300) * yTileSize), Mapp.BackColor, BF
  Mapp.Line (0, (WindowY + 1) * yTileSize)-((WindowX + 1) * xTileSize, (WindowY + 300) * yTileSize), Mapp.BackColor, BF
End If


End Sub

Private Sub HScroll_Change()
  CameraX = HScroll.value
  DrawMap 0, 0, xMapSize, yMapSize
End Sub

Private Sub HScroll_Scroll()
  HScroll_Change
End Sub


Private Sub Mapp_KeyDown(KeyCode As Integer, Shift As Integer)
  Form_KeyDown KeyCode, Shift
End Sub

Private Sub Mapp_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
  Dim x1, y1, x2, y2, xPos, yPos, CurX, CurY, I, T, CurOBJ
  If EditMode = 0 Then
    Mapp_MouseMove Button, Shift, X, Y
  Else
    CurOBJ = -1
    xPos = X \ xTileSize + CameraX
    yPos = Y \ yTileSize + CameraY
    If xPos > xMapSize Then xPos = xMapSize
    If yPos > yMapSize Then yPos = yMapSize
    
    With Mapp
      If X > .Width - 1 Or X < 0 Or Y > .Height - 1 Or Y < 0 Then Exit Sub
    End With
    'Position Cursor
    x1 = (xPos - CameraX) * xTileSize
    y1 = (yPos - CameraY) * yTileSize
    With MapCursor
      .Left = x1
      .Top = y1
      .Width = xTileSize
      .Height = yTileSize
    End With
    If Button = 1 Then
      For I = 0 To NumObj
        If xPos = Obj(I).X And yPos = Obj(I).Y And (Obj(I).M And 127) = 1 Then
          SelectedObj = I
          mnuProps1.Caption = "Teleporter " + Trim(Str(SelectedObj)) + " selected!"
          mnuProps2.Visible = False
          mnuProps2.Caption = "(" + Trim(Str(Obj(SelectedObj).X)) + ", " + Trim(Str(Obj(SelectedObj).Y)) + ") at map " + Hex2(Obj(SelectedObj).M) + " - " + MapNames(Obj(SelectedObj).M)
          mnuProps3.Visible = False
          mnuProps3.Caption = ""
          MapEditor.PopupMenu mnuProps
         Exit For
        End If
      Next
    End If

    lblXY.Caption = "X:" + Trim(Str(xPos)) + " Y:" + Trim(Str(yPos))

    If Button = 2 Then
      If SelectedObj = -1 Then Exit Sub
      sXpos = xPos
      sYpos = yPos
      mnuStairs.Checked = Obj(SelectedObj).M And &H80
      mnuProps0.Caption = "Selected: " + Trim(Str(SelectedObj)) + " (" + Trim(Str(Obj(SelectedObj).X)) + ", " + Trim(Str(Obj(SelectedObj).Y)) + ") at map " + Hex2(Obj(SelectedObj).M And 127) + " - " + MapNames(Obj(SelectedObj).M And 127)
      mnuProps1.Caption = "TO: " + Trim(Str(SelectedObj Xor 256)) + " (" + Trim(Str(Obj(SelectedObj Xor 256).X)) + ", " + Trim(Str(Obj(SelectedObj Xor 256).Y)) + ") at map " + Hex2(Obj(SelectedObj Xor 256).M And 127) + " - " + MapNames(Obj(SelectedObj Xor 256).M And 127)
      mnuProps2.Visible = False
      mnuProps2.Caption = "(" + Trim(Str(Obj(SelectedObj).X)) + ", " + Trim(Str(Obj(SelectedObj).Y)) + ") at map " + Hex2(Obj(SelectedObj).M) + " - " + MapNames(Obj(SelectedObj).M)
      mnuProps3.Visible = False
      mnuProps3.Caption = ""
      mnuProps.Visible = True
      MapEditor.PopupMenu mnuPop
    End If
  End If
End Sub

Private Sub Mapp_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
  Dim x1, y1, x2, y2, xPos, yPos, CurX, CurY, I, T, CurOBJ
  If EditMode = 0 Then
    With Mapp
      If X < .Left Or X > .Width Or Y < .Top Or Y > .Height Then Exit Sub
    End With
    xPos = X \ xTileSize + CameraX
    yPos = Y \ yTileSize + CameraY
    
    If xPos > xMapSize Then xPos = xMapSize
    If yPos > yMapSize Then yPos = yMapSize
    
    If Button And 2 Then
    Else
      If xPos + xBrushSize > xMapSize Then xPos = xMapSize - xBrushSize
      If yPos + yBrushSize > yMapSize Then yPos = yMapSize - yBrushSize
    End If
    
    lblXY.Caption = "X:" + Trim(Str(xPos)) + " Y:" + Trim(Str(yPos))
    
    x1 = (xPos - CameraX) * xTileSize
    y1 = (yPos - CameraY) * yTileSize
    If Button = 0 Then
      With MapCursor
        .Left = x1
        .Top = y1
        .Width = xBrushSize * xTileSize + xTileSize
        .Height = yBrushSize * yTileSize + yTileSize
      End With
    ElseIf Button = 1 Then
      With MapCursor
        .Left = x1
        .Top = y1
        .Width = xBrushSize * xTileSize + xTileSize
        .Height = yBrushSize * yTileSize + yTileSize
      End With
      For CurX = 0 To xBrushSize
      For CurY = 0 To yBrushSize
        map(CurX + xPos, CurY + yPos) = Brush(CurX, CurY)
      Next
      Next
      SmoothMap xPos - 1, yPos - 1, xBrushSize + xPos + 1, yBrushSize + yPos + 1
      DrawMap xPos - 1, yPos - 1, xBrushSize + xPos + 1, yBrushSize + yPos + 1
      
      CountSize
    ElseIf Button = 2 Then
      
      If xPos > xMapSize Then xPos = xMapSize - 1
      If xPos < 0 Then xPos = 0
      If yPos > yMapSize Then yPos = yMapSize
      If yPos < 0 Then yPos = 0
      
      If xStart = -1 Then
        xStart = xPos
        yStart = yPos
      End If
      
      With MapCursor
        If xPos < xStart Then
          .Left = (xPos - CameraX) * xTileSize
        Else
          .Left = (xStart - CameraX) * xTileSize
        End If
        If yPos < yStart Then
          .Top = (yPos - CameraY) * yTileSize
        Else
          .Top = (yStart - CameraY) * yTileSize
        End If
        xBrushSize = Abs(xStart - xPos)
        yBrushSize = Abs(yStart - yPos)
        
        .Width = xBrushSize * xTileSize + xTileSize
        .Height = yBrushSize * yTileSize + yTileSize
      End With
      
      
      xEnd = xPos
      yEnd = yPos
      
    End If
  Else
'    CurOBJ = -1
    With Mapp
      If X < .Left Or X > .Width Or Y < .Top Or Y > .Height Then Exit Sub
    End With
    xPos = X \ xTileSize + CameraX
    yPos = Y \ yTileSize + CameraY
    
    lblXY.Caption = "X:" + Trim(Str(xPos)) + " Y:" + Trim(Str(yPos))
    
    x1 = (xPos - CameraX) * xTileSize
    y1 = (yPos - CameraY) * yTileSize
    With MapCursor
      .Left = x1
      .Top = y1
    End With
  End If
End Sub

Private Sub Mapp_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
  Dim CurX, CurY
 If EditMode = 0 Then
  If Button = 2 Then
    SwapIfLess xEnd, xStart
    SwapIfLess yEnd, yStart
    If xStart < 0 Then Exit Sub
    If yStart < 0 Then Exit Sub
    xBrushSize = Abs(xEnd - xStart)
    yBrushSize = Abs(yEnd - yStart)
    For CurX = 0 To xBrushSize
    For CurY = 0 To yBrushSize
      Brush(CurX, CurY) = map(xStart + CurX, yStart + CurY)
    Next
    Next
    sel1.Visible = True
    sel1.Left = Brush(0, 0) * xTileSize
    sel1.Top = 0

    xStart = -1: yStart = -1
  End If
 Else
  
 End If
End Sub

Private Sub mnuPlace_Click()
  Obj(SelectedObj).X = sXpos
  Obj(SelectedObj).Y = sYpos
  DrawMap 0, 0, xMapSize, yMapSize
End Sub

Private Sub mnuStairs_Click()
  Obj(SelectedObj).M = Obj(SelectedObj).M Xor &H80
End Sub

Private Sub pTileset_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
  If EditMode = 1 Then Exit Sub
  pTileset_MouseMove Button, Shift, X, Y
  Mapp.SetFocus
End Sub

Private Sub pTileset_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
  If EditMode = 1 Then Exit Sub
  Dim x1, y1, Z, CurX, CurY
  x1 = X \ xTileSize
  y1 = Y \ yTileSize
  Z = (y1 Mod tHeight) + (x1 * tHeight)
  If Z > 239 Or Z < 0 Then Exit Sub
  If Button And 2 Then
    If MsgBox("Warning, this is the global tile replacer.  (you right clicked on the palette to get this)" + vbCrLf + "Replace all tiles that you right clicked on with the current pen?", vbYesNoCancel) <> vbYes Then Exit Sub
    For CurX = 0 To xMapSize
    For CurY = 0 To yMapSize
      If map(CurX, CurY) = Z Then map(CurX, CurY) = Brush(0, 0)
    Next
    Next
    SmoothMap 0, 0, xMapSize, yMapSize
    DrawMap 0, 0, xMapSize, yMapSize
    CountSize
    Exit Sub
  End If
  If Button Then
    xBrushSize = optBrushSize
    yBrushSize = optBrushSize
    For CurX = 0 To xBrushSize
    For CurY = 0 To yBrushSize
      Brush(CurX, CurY) = Z
    Next
    Next
    sel1.Visible = True
    sel1.Left = x1 * xTileSize
    sel1.Top = y1 * yTileSize
  End If
  Mapp.SetFocus
End Sub

Private Sub TileScroller_Change()
  pTileset.Left = -TileScroller.value
End Sub

Private Sub TileScroller_Scroll()
  TileScroller_Change
End Sub

Private Sub VScroll_Change()
  CameraY = VScroll.value
  DrawMap 0, 0, xMapSize, yMapSize
End Sub

Private Sub VScroll_Scroll()
  VScroll_Change
End Sub
