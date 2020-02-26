object fConnect: TfConnect
  Left = 520
  Top = 201
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1047#1074#1086#1088#1086#1090#1085#1110#1081' '#1079#1074#39#1103#1079#1086#1082
  ClientHeight = 239
  ClientWidth = 377
  Color = clGradientInactiveCaption
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 24
    Width = 314
    Height = 39
    Caption = 
      #1047#1074#1086#1088#1086#1090#1085#1110#1081' '#1079#1074#39#1103#1079#1086#1082' '#1076#1086#1089#1090#1091#1087#1085#1080#1081' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1072#1084', '#1103#1082#1110' '#1108' '#1074#1083#1072#1089#1085#1080#1082#1072#1084#1080' '#1083#1110#1094#1077#1085 +
      #1079#1110#1081#1085#1086#1111' '#1074#1077#1088#1089#1110#1111' '#1087#1088#1086#1075#1088#1072#1084#1080'. '#1071#1082#1097#1086' '#1042#1080' '#1108' '#1074#1083#1072#1089#1085#1080#1082#1086#1084' '#1090#1072#1082#1086#1111' '#1074#1077#1088#1089#1110#1111', '#1074#1074#1077#1076#1110#1090 +
      #1100', '#1073#1091#1076#1100' '#1083#1072#1089#1082#1072', '#1082#1083#1102#1095' '#1072#1082#1090#1080#1074#1072#1094#1110#1111'.'
    WordWrap = True
  end
  object Label2: TLabel
    Left = 24
    Top = 152
    Width = 50
    Height = 13
    Caption = #1050#1086#1085#1090#1072#1082#1090#1080':'
  end
  object Label3: TLabel
    Left = 24
    Top = 176
    Width = 54
    Height = 13
    Caption = '------------------'
  end
  object Label4: TLabel
    Left = 88
    Top = 176
    Width = 126
    Height = 13
    Caption = '<'#1110#1085#1092#1086#1088#1084#1072#1094#1110#1102' '#1087#1088#1080#1093#1086#1074#1072#1085#1086'>'
  end
  object Label5: TLabel
    Left = 24
    Top = 192
    Width = 54
    Height = 13
    Caption = '------------------'
  end
  object Label6: TLabel
    Left = 88
    Top = 192
    Width = 126
    Height = 13
    Caption = '<'#1110#1085#1092#1086#1088#1084#1072#1094#1110#1102' '#1087#1088#1080#1093#1086#1074#1072#1085#1086'>'
  end
  object Label7: TLabel
    Left = 24
    Top = 208
    Width = 54
    Height = 13
    Caption = '------------------'
  end
  object Label8: TLabel
    Left = 88
    Top = 208
    Width = 126
    Height = 13
    Caption = '<'#1110#1085#1092#1086#1088#1084#1072#1094#1110#1102' '#1087#1088#1080#1093#1086#1074#1072#1085#1086'>'
  end
  object Edit: TEdit
    Left = 64
    Top = 88
    Width = 217
    Height = 21
    TabOrder = 0
    OnChange = EditChange
  end
  object bOk: TButton
    Left = 136
    Top = 120
    Width = 65
    Height = 25
    Caption = #1054#1082
    Enabled = False
    TabOrder = 1
    OnClick = bOkClick
  end
end
