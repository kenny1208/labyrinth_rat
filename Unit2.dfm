object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Mouse in a Maze by 11160801'
  ClientHeight = 325
  ClientWidth = 550
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnResize = FormResize
  TextHeight = 15
  object Splitter1: TSplitter
    Left = 169
    Top = 0
    Height = 325
    ExplicitLeft = 192
    ExplicitTop = 248
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 169
    Height = 325
    Align = alLeft
    Caption = 'Panel1'
    TabOrder = 0
    object PageControl3: TPageControl
      Left = 1
      Top = 1
      Width = 167
      Height = 323
      ActivePage = TabSheet6
      Align = alClient
      TabOrder = 0
      object TabSheet6: TTabSheet
        Caption = 'Mouse in a Maze'
        object Label1: TLabel
          Left = 17
          Top = 24
          Width = 49
          Height = 15
          Caption = 'Height'#65306
        end
        object Label2: TLabel
          Left = 17
          Top = 50
          Width = 45
          Height = 15
          Caption = 'Width'#65306
        end
        object Edit1: TEdit
          Left = 68
          Top = 21
          Width = 73
          Height = 23
          TabOrder = 0
          Text = '19'
        end
        object Edit2: TEdit
          Left = 68
          Top = 50
          Width = 73
          Height = 23
          TabOrder = 1
          Text = '19'
        end
        object Button1: TButton
          Left = 17
          Top = 104
          Width = 124
          Height = 33
          Caption = 'Generate Maze'
          TabOrder = 2
          OnClick = Button1Click
        end
        object Button2: TButton
          Left = 17
          Top = 143
          Width = 124
          Height = 33
          Caption = 'Save Maze'
          TabOrder = 3
          OnClick = Button2Click
        end
        object Button3: TButton
          Left = 17
          Top = 182
          Width = 124
          Height = 33
          Caption = 'Load Maze'
          TabOrder = 4
          OnClick = Button3Click
        end
        object Button4: TButton
          Left = 17
          Top = 246
          Width = 124
          Height = 33
          Caption = 'Find a tour'
          TabOrder = 5
          OnClick = Button4Click
        end
      end
    end
  end
  object PageControl1: TPageControl
    Left = 172
    Top = 0
    Width = 378
    Height = 325
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Tour in Memo'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 370
        Height = 295
        Align = alClient
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Tour in StringGrid'
      ImageIndex = 1
      object Memo2: TMemo
        Left = 0
        Top = 0
        Width = 370
        Height = 295
        Align = alClient
        Lines.Strings = (
          'Memo2')
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 370
        Height = 295
        Align = alClient
        TabOrder = 1
        OnDrawCell = StringGrid1DrawCell
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 296
    Top = 58
  end
  object SaveDialog1: TSaveDialog
    Left = 109
    Top = 235
  end
end
