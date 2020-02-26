unit Main;

interface

uses
  SysUtils, Classes, Controls, Forms,
  Dialogs, StdCtrls, Grids, ExtCtrls, Menus, MPlayer,
  Buttons, IniFiles, jpeg;

type
  TfMain = class(TForm)
    sField: TStringGrid;
    pnlHorizontal1: TPanel;
    pnlHorizontal2: TPanel;
    pnlVertical1: TPanel;
    pnlVertical2: TPanel;
    btnNewGame: TButton;
    btnAgain: TButton;
    btnCheckSudoku: TButton;
    btnHint: TButton;
    btnGiveUp: TButton;
    btnSave: TBitBtn;
    btnLoad: TBitBtn;
    MainMenu: TMainMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    N4: TMenuItem;
    N5: TMenuItem;
    N6: TMenuItem;
    N7: TMenuItem;
    N8: TMenuItem;
    N9: TMenuItem;
    N10: TMenuItem;
    Image: TImage;
    mpSound: TMediaPlayer;
    cbbDifficulty: TComboBox;
    dlgSave: TSaveDialog;
    dlgOpen: TOpenDialog;
    procedure btnNewGameClick(Sender: TObject);
    procedure btnAgainClick(Sender: TObject);
    procedure btnCheckSudokuClick(Sender: TObject);
    procedure btnHintClick(Sender: TObject);
    procedure btnGiveUpClick(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure btnLoadClick(Sender: TObject);
    procedure N3Click(Sender: TObject);
    procedure N4Click(Sender: TObject);
    procedure N5Click(Sender: TObject);
    procedure N6Click(Sender: TObject);
    procedure N7Click(Sender: TObject);
    procedure N9Click(Sender: TObject);
    procedure N10Click(Sender: TObject);
    procedure sFieldSelectCell(Sender: TObject; ACol, ARow: Integer;
      var CanSelect: Boolean);
    procedure FormCreate(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormDestroy(Sender: TObject);

  private
    { Private declarations }
  public
    Activated: string[12];
    { Public declarations }
  end;

type Cell = record //��� ������� ������
    Tried: array[1..9] of Boolean;
    Value: 0..9;
    Filled: Boolean;
  end;
  Tsdk = record //��� ����� ������
    Primary: array[1..9, 1..9] of Cell;
    Current: array[1..9, 1..9] of Cell;
    Solved: array[1..9, 1..9] of string[3];
    Hints: Byte;
    GameDifficulty: Byte;
    GameActive: Boolean;
  end;

var
  fMain: TfMain; //������� �����
  Field: array[1..9, 1..9] of Cell; //����� ������� �������� ����
  TempField: array[1..9, 1..9] of Cell; //����������� ������ ������� ���
  Difficulty: Byte; //ʳ������ ���������� �������
  Solutions: Integer; //ʳ������ ����'����
  Hints: Byte; //ʳ������ ������������ �������
  GameActive: Boolean; //���� ��� (�����/��������)
  Checked: Boolean; //���� ����������� �������� ����������� ����
  SudokuGame: Tsdk; //����� ��� ���������� � �������� ��� � ����
  FileSDK: file of Tsdk; //������� �����
  FileName: string; //����� �����
  WasSaved: Boolean; //�� ���� ��������� ���
  Activated: string[12]; //�� ���� ������� ���� ���������

implementation

uses Numbers, AboutProgram, AboutGame, Authors, SaveGame;

{$R *.dfm}

//����� ������� � ����� Field

procedure ResetCell(var c: Cell);
var i: 1..9;
begin
  c.Value := 0;
  for i := 1 to 9 do c.Tried[i] := False;
  c.Filled := False;
end;

//�������� ���������� �������� ������� � ����� Field

procedure NextCell(var r, c: Byte);
begin
  if c < 9 then c := c + 1
  else
  begin
    r := r + 1; ;
    c := 1;
  end;
end;

//��������, �� �� �������� ������ Field ��������

function AllFilled: Boolean;
var
  r, c: 1..9;
begin
  AllFilled := False;
  for r := 1 to 9 do
    for c := 1 to 9 do
      if Field[r, c].Filled = False then Exit;
  AllFilled := True;
end;

//��������, �� �� ������� �������� ���� sField ��������

function AllSolved: Boolean;
var
  r, c: 1..9;
begin
  AllSolved := False;
  for r := 1 to 9 do
    for c := 1 to 9 do
      if (Field[r, c].Filled = False) and (Length(fMain.sField.Cells[r - 1, c - 1]) = 0) then Exit;
  AllSolved := True;
end;

//�������� ������� ����������� ����� ���� ������� �� ������ �� ��� ��������� ����

function CountTried(c: Cell): Byte;
var
  i, count: Byte;
begin
  count := 0;
  for i := 1 to 9 do
    if c.Tried[i] = True then inc(Count);
  CountTried := count;
end;

//��������, �� ����� Number � ������������ Row, Column ���� ���������� � ������� 3x3

function CheckCellBox(Number, Row, Column: byte): Boolean;
var
  c, r: 1..9;
begin
  CheckCellBox := False;
  if (Column mod 3) = 0 then Column := Column - 2
  else Column := (Column div 3) * 3 + 1;
  if (Row mod 3) = 0 then Row := Row - 2
  else Row := (Row div 3) * 3 + 1;
  for r := Row to Row + 2 do
    for c := Column to Column + 2 do
      if (Field[r, c].Filled) and (Field[r, c].Value = Number) then Exit;
  CheckCellBox := True;
end;

//��������, �� ����� Number � ������������ Row, Column ���� ���������� � ����� Field, ��������������� �� ��� ��������� ����

function CheckNumberFill(Number, Row, Column: byte): Boolean;
var
  i: 1..9;
begin
  CheckNumberFill := False;
  if CheckCellBox(Number, Row, Column) = False then Exit
  else
  begin
    for i := 1 to 9 do
    begin
      if Field[Row, i].Value = Number then Exit;
    end;
    for i := 1 to 9 do
    begin
      if Field[i, Column].Value = Number then Exit;
    end;
  end;
  CheckNumberFill := True;
end;

//��������, �� ����� Number � ������������ Row, Column ���� ���������� � ����� Field, ��������������� �� ��� �������� �������� �����

function CheckNumberSolve(Number, Row, Column: byte): Boolean;
var
  i: 1..9;
begin
  CheckNumberSolve := False;
  if CheckCellBox(Number, Row, Column) = False then Exit
  else
  begin
    for i := 1 to 9 do
    begin
      if (Field[Row, i].Filled) and (Field[Row, i].Value = Number) then Exit;
    end;
    for i := 1 to 9 do
    begin
      if (Field[i, Column].Filled) and (Field[i, Column].Value = Number) then Exit;
    end;
  end;
  CheckNumberSolve := True;
end;

//�������� ������� ��������� ����� ��� �������

function CountVariants(Row, Column: Byte): Byte;
var
  i, count: Byte;
begin
  count := 0;
  for i := 1 to 9 do
    if CheckNumberSolve(i, Row, Column) then inc(count);
  CountVariants := count;
end;

//��������� ����� ������� � ��������� ������� �������

procedure FindMinPoint(var r, c: Byte);
var
  a, b, min: 1..9;
begin
  min := 9;
  for a := 1 to 9 do
    for b := 1 to 9 do
      if Field[a, b].Filled then Continue
      else if CountVariants(a, b) < min then
      begin
        min := CountVariants(a, b);
        r := a;
        c := b;
      end;
end;

//������ ����'��� ��� � ��������� ����� Solutions �������� ������� ����'����

procedure Solve;
var
  r, c, i, num: Byte;
begin
  if AllFilled then
  begin
    inc(Solutions);
    Exit;
  end
  else
  begin
    FindMinPoint(r, c);
    for i := 1 to 9 do
      if CheckNumberSolve(i, r, c) then
      begin
        num := Field[r, c].Value;
        Field[r, c].Value := i;
        Field[r, c].Filled := True;
        Solve;
        Field[r, c].Value := num;
        Field[r, c].Filled := False;
      end;
  end;
end;

//������ ��������� ������ ����

procedure Generate(Row, Column: Byte);
var
  num, r, c: Byte;
begin
  Randomize;
  while Field[9, 9].Filled = False do
  begin
    r := Row;
    c := Column;
    if CountTried(Field[Row, Column]) < 9 then
    begin
      repeat
        num := Random(9) + 1;
      until Field[Row, Column].Tried[num] = False;
      if CheckNumberFill(num, Row, Column) then
      begin
        Field[r, c].Value := num;
        Field[r, c].Tried[num] := True;
        Field[r, c].Filled := True;
        NextCell(r, c);
        if (r <= 9) and (c <= 9) then Generate(r, c);
      end
      else Field[r, c].Tried[num] := True;
    end
    else
    begin
      ResetCell(Field[r, c]);
      Exit;
    end;
  end;
end;

//������� ������� � ��������� ����� Difficulty ������� ������� ����� �����, ��� ��� ���� ������ ����'����

procedure HideCells;
var
  r, c, count: byte;
begin
  Randomize;
  count := 0;
  while count < Difficulty do
  begin
    r := Random(9) + 1;
    c := Random(9) + 1;
    if Field[r, c].Filled = False then Continue
    else
    begin
      Field[r, c].Filled := False;
      Solve;
      if Solutions = 1 then Inc(count)
      else Field[r, c].Filled := True;
      Solutions := 0;
    end;
  end;
end;

//�������� ������� �������, ��������� �������

function CountMistakes: Byte;
var
  r, c, mistakes: Byte;
begin
  mistakes := 0;
  for r := 1 to 9 do
    for c := 1 to 9 do
      if (Field[r, c].Filled = False) and (' ' + IntToStr(Field[r, c].Value) <> fMain.sField.Cells[r - 1, c - 1]) then inc(mistakes);
  CountMistakes := mistakes;
end;

//������ ���� �������� ���

procedure TfMain.btnNewGameClick(Sender: TObject);
var
  r, c: 1..9;
begin
  if WasSaved = False then
  begin
    fSavePrevGame.ShowModal;
    if fSavePrevGame.SaveChoice = True then
      if dlgSave.Execute = False then Exit;
  end;
  case cbbDifficulty.ItemIndex of
    0: Difficulty := 36;
    1: Difficulty := 45;
    2: Difficulty := 52;
  end;
  GameActive := True;
  Checked := False;
  WasSaved := False;
  sField.Enabled := True;
  Solutions := 0;
  Hints := 0;
  btnHint.Enabled := True;
  btnGiveUp.Enabled := True;
  for r := 1 to 9 do
    for c := 1 to 9 do
      ResetCell(Field[r, c]);
  Generate(1, 1);
  HideCells;
  for r := 1 to 9 do
    for c := 1 to 9 do
    begin
      TempField[r, c] := Field[r, c];
      if Field[r, c].Filled then
        sField.Cells[r - 1, c - 1] := ' ' + IntToStr(Field[r, c].Value) + '.'
      else sField.Cells[r - 1, c - 1] := '';
    end;
end;

//��������� ������� ��� ��������

procedure TfMain.btnAgainClick(Sender: TObject);
var
  r, c: 1..9;
begin
  for r := 1 to 9 do
    for c := 1 to 9 do
    begin
      Field[r, c] := TempField[r, c];
      if TempField[r, c].Filled then sField.Cells[r - 1, c - 1] := ' ' + IntToStr(TempField[r, c].Value) + '.'
      else sField.Cells[r - 1, c - 1] := '';
    end;
  Hints := 0;
  GameActive := True;
  Checked := False;
  btnHint.Enabled := True;
  btnGiveUp.Enabled := True;
end;

//������ �������� ����'����

procedure TfMain.btnCheckSudokuClick(Sender: TObject);
begin
  if AllSolved = False then
  begin
    ShowMessage('��������, ���� �����, ��� ����!');
    Exit;
  end
  else if CountMistakes = 0 then
  begin
    if Hints = 0 then ShowMessage('������ ����"���� ���������. ³����!!!')
    else if Hints = 81 then ShowMessage('�� �������!!!')
    else ShowMessage('������ ����"����� ���������, ��� � ��������� �������. ����������� �������: ' + IntToStr(Hints) + ' � ' + IntToStr(Difficulty));
    GameActive := False;
    btnHint.Enabled := False;
    btnGiveUp.Enabled := False;
  end
  else ShowMessage('�� ����, ������ ����"����� �����������. �������� �������: ' + IntToStr(CountMistakes) + '. ��������� ��!');
end;

//³������ ������� � ��������� ������� �������

procedure TfMain.btnHintClick(Sender: TObject);
var
  r, c: Byte;
begin
  if (GameActive = False) or (AllFilled) then Exit;
  inc(Hints);
  repeat
    FindMinPoint(r, c);
    if sField.Cells[r - 1, c - 1] = ' ' + IntToStr(Field[r, c].Value) then Field[r, c].Filled := True;
  until sField.Cells[r - 1, c - 1] <> ' ' + IntToStr(Field[r, c].Value);
  Field[r, c].Filled := True;
  sField.Cells[r - 1, c - 1] := ' ' + IntToStr(Field[r, c].Value) + '!';
  if (AllSolved) and ((Checked = False) or (CountMistakes = 0)) then
  begin
    btnCheckSudoku.Click;
    Checked := True;
  end;
end;

//������� ������� ��� �� ������ ���������� ����'����

procedure TfMain.btnGiveUpClick(Sender: TObject);
var
  r, c: 1..9;
begin
  if (GameActive = False) or (AllFilled) then Exit;
  for r := 1 to 9 do
    for c := 1 to 9 do
    begin
      if Field[r, c].Filled = False then sField.Cells[r - 1, c - 1] := ' ' + IntToStr(Field[r, c].Value);
      Field[r, c].Filled := True;
    end;
  Hints := 81;
  btnHint.Enabled := False;
  btnGiveUp.Enabled := False;
  GameActive := False;
end;

//������� ���� ������ �����

procedure TfMain.sFieldSelectCell(Sender: TObject; ACol, ARow: Integer;
  var CanSelect: Boolean);
begin
  if GameActive = False then Exit;
  if not Field[ACol + 1, Arow + 1].Filled then
  begin
    fNumbers.ShowModal;
    if fNumbers.Num = 'X' then Exit
    else if fNumbers.Num = '0' then sField.Cells[ACol, Arow] := ''
    else sField.Cells[Acol, Arow] := ' ' + fNumbers.Num;
  end;
  if (AllSolved) and ((Checked = False) or (CountMistakes = 0)) then
  begin
    btnCheckSudoku.Click;
    Checked := True;
  end;
end;

//������ ��� � ����

procedure TfMain.N6Click(Sender: TObject);
var
  r, c: 1..9;
begin
  if dlgSave.Execute = False then Exit;
  WasSaved := True;
  for r := 1 to 9 do
    for c := 1 to 9 do
    begin
      SudokuGame.Primary[r, c] := TempField[r, c];
      SudokuGame.Current[r, c] := Field[r, c];
      SudokuGame.Solved[r, c] := sField.Cells[r - 1, c - 1];
      SudokuGame.Hints := Hints;
      SudokuGame.GameDifficulty := Difficulty;
      SudokuGame.GameActive := GameActive;
    end;
  begin
    FileName := dlgSave.FileName;
    if FileName = '' then FileName := 'Game';
    if Copy(FileName, Length(FileName) - 3, 4) <> '.sdk' then FileName := FileName + '.sdk';
    AssignFile(FileSDK, FileName);
    Rewrite(FileSDK);
    Write(FileSDK, SudokuGame);
    CloseFile(FileSDK);
  end;
end;

//³������ ��� � �����

procedure TfMain.N7Click(Sender: TObject);
var
  r, c: 1..9;
begin
  if WasSaved = False then
  begin
    fSavePrevGame.ShowModal;
    if fSavePrevGame.SaveChoice = True then N6.Click;
  end;
  if (dlgOpen.Execute = False) or (dlgOpen.FileName = '') then Exit;
  begin
    FileName := dlgOpen.FileName;
    AssignFile(FileSDK, FileName);
    Reset(FileSDK);
    Read(FileSDK, SudokuGame);
    CloseFile(FileSDK);
  end;
  for r := 1 to 9 do
    for c := 1 to 9 do
    begin
      TempField[r, c] := SudokuGame.Primary[r, c];
      Field[r, c] := SudokuGame.Current[r, c];
      sField.Cells[r - 1, c - 1] := SudokuGame.Solved[r, c];
    end;
  Hints := SudokuGame.Hints;
  Difficulty := SudokuGame.GameDifficulty;
  GameActive := SudokuGame.GameActive;
  case Difficulty of
    36: cbbDifficulty.ItemIndex := 0;
    45: cbbDifficulty.ItemIndex := 1;
    54: cbbDifficulty.ItemIndex := 2;
  end; ;
  Checked := True;
  WasSaved := True;
  if GameActive then
  begin
    btnHint.Enabled := True;
    btnGiveUp.Enabled := True;
  end
  else
  begin
    btnHint.Enabled := False;
    btnGiveUp.Enabled := False;
  end;
end;

//������ ���� ��� � ����

procedure TfMain.N5Click(Sender: TObject);
begin
  btnNewGame.Click;
end;

//�������� ���� ��� �������

procedure TfMain.FormActivate(Sender: TObject);
begin
  wassaved := True;
  btnNewGame.Click;
  WasSaved := False;
  if FileExists('sound.wav') then mpSound.Open
  else if FileExists('sound.mp3') then
  begin
    mpSound.FileName := 'sound.mp3';
    mpSound.Open;
  end
  else mpSound.Visible := False;
end;

//������ ������������ � ����

procedure TfMain.btnLoadClick(Sender: TObject);
begin
  N7.Click;
end;

//������ ���������� � ����

procedure TfMain.btnSaveClick(Sender: TObject);
begin
  N6.Click;
end;

//������ ���� "��� ��������"

procedure TfMain.N10Click(Sender: TObject);
begin
  fAboutProgram.ShowModal;
end;

//������ ���� "��� ���"

procedure TfMain.N3Click(Sender: TObject);
begin
  fAboutGame.ShowModal;
end;

//������ ���� "��� ������"

procedure TfMain.N4Click(Sender: TObject);
begin
  fAuthors.ShowModal;
end;

//�������� ��������

procedure TfMain.N9Click(Sender: TObject);
begin
  Close;
end;

//���������� ���������

procedure TfMain.FormDestroy(Sender: TObject);
var
  ini: TIniFile;
begin
  ini := TIniFile.Create(ExtractFilePath(Application.ExeName) + 'options.ini');
  ini.WriteInteger('Position', 'Top', fMain.Top);
  ini.WriteInteger('Position', 'Left', fMain.Left);
  ini.WriteInteger('Difficulty', 'Level', fMain.cbbDifficulty.ItemIndex);
  ini.WriteString('Activation', 'Activated', Activated);
  ini.Free;
end;

//������������ ���������� ���������

procedure TfMain.FormCreate(Sender: TObject);
var
  ini: TIniFile;
begin
  ini := TIniFile.Create(ExtractFilePath(Application.ExeName) + 'options.ini');
  fMain.Top := ini.ReadInteger('Position', 'Top', 140);
  fMain.Left := ini.ReadInteger('Position', 'Left', 391);
  fMain.cbbDifficulty.ItemIndex := ini.ReadInteger('Difficulty', 'Level', 1);
  Activated := ini.ReadString('Activation', 'Activated', 'No Password!');
  ini.Free;
end;

//���������� �������� ��� ����� �������

procedure TfMain.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if WasSaved = False then
  begin
    fSavePrevGame.ShowModal;
    if fSavePrevGame.SaveChoice = True then N6.Click;
  end;
end;

end.

