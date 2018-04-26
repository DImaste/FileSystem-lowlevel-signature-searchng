object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'NTFS Shark'
  ClientHeight = 423
  ClientWidth = 803
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PathEdit: TLabeledEdit
    Left = 8
    Top = 24
    Width = 250
    Height = 21
    EditLabel.Width = 155
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1091#1090#1100' '#1082' '#1080#1084#1077#1085#1080' '#1092#1072#1081#1083#1072' ('#1088#1072#1079#1076#1077#1083#1072')'
    TabOrder = 0
    Text = '\\.\E:'
  end
  object ResultTree: TVirtualStringTree
    Left = 489
    Top = 105
    Width = 304
    Height = 296
    Header.AutoSizeIndex = 0
    Header.Font.Charset = DEFAULT_CHARSET
    Header.Font.Color = clWindowText
    Header.Font.Height = -11
    Header.Font.Name = 'Tahoma'
    Header.Font.Style = []
    TabOrder = 1
    TreeOptions.PaintOptions = [toHotTrack, toShowBackground, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowTreeLines, toShowVertGridLines, toUseBlendedImages, toFullVertGridLines]
    OnGetText = ResultTreeGetText
    Columns = <
      item
        Position = 0
        Width = 100
      end
      item
        Position = 1
        Width = 100
      end
      item
        Position = 2
        Width = 100
      end>
  end
  object SearchButton: TButton
    Left = 183
    Top = 62
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 2
    OnClick = SearchButtonClick
  end
  object Television: TListBox
    Left = 8
    Top = 105
    Width = 449
    Height = 264
    ItemHeight = 13
    TabOrder = 3
  end
  object Start: TLabeledEdit
    Left = 8
    Top = 64
    Width = 73
    Height = 21
    EditLabel.Width = 61
    EditLabel.Height = 13
    EditLabel.Caption = 'Start Cluster'
    TabOrder = 4
    Text = 'start'
  end
  object LogBox: TListBox
    Left = 488
    Top = 8
    Width = 305
    Height = 91
    ItemHeight = 13
    TabOrder = 5
  end
  object Save: TButton
    Left = 345
    Top = 62
    Width = 112
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083
    TabOrder = 6
    OnClick = SaveClick
  end
  object StopButton: TButton
    Left = 264
    Top = 62
    Width = 75
    Height = 25
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100
    TabOrder = 7
    OnClick = StopButtonClick
  end
  object Progress: TProgressBar
    Left = 8
    Top = 375
    Width = 449
    Height = 26
    TabOrder = 8
  end
  object End: TLabeledEdit
    Left = 96
    Top = 64
    Width = 81
    Height = 21
    EditLabel.Width = 55
    EditLabel.Height = 13
    EditLabel.Caption = 'End Cluster'
    TabOrder = 9
    Text = 'end'
  end
  object FsType: TComboBox
    Left = 264
    Top = 24
    Width = 193
    Height = 21
    TabOrder = 10
    Text = 'NTFS'
    Items.Strings = (
      'NTFS'
      'FAT'
      'exFAT')
  end
end
