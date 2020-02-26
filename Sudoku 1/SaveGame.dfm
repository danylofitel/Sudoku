object fSavePrevGame: TfSavePrevGame
  Left = 359
  Top = 251
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1059#1074#1072#1075#1072'!'
  ClientHeight = 93
  ClientWidth = 257
  Color = clGradientInactiveCaption
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 0
    Top = 8
    Width = 257
    Height = 33
    Alignment = taCenter
    AutoSize = False
    Caption = #1047#1073#1077#1088#1077#1075#1090#1080' '#1087#1086#1090#1086#1095#1085#1091' '#1075#1088#1091'?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object btn_yes: TButton
    Left = 40
    Top = 48
    Width = 75
    Height = 25
    Caption = #1058#1072#1082
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = btn_yesClick
  end
  object btn_no: TButton
    Left = 144
    Top = 48
    Width = 75
    Height = 25
    Caption = #1053#1110
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btn_noClick
  end
end
