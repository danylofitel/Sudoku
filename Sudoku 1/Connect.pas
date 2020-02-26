unit Connect;

interface

uses
  Classes, Controls, Forms,
  Dialogs, StdCtrls;

type
  TfConnect = class(TForm)
    Edit: TEdit;
    bOk: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    procedure EditChange(Sender: TObject);
    procedure bOkClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fConnect: TfConnect;

implementation

uses Main;

{$R *.dfm}

procedure TfConnect.EditChange(Sender: TObject);
begin
  if Edit.Text = '' then bOk.Enabled := False
  else bOk.Enabled := true;
end;

procedure TfConnect.bOkClick(Sender: TObject);
begin
  if Edit.Text = '1801-1605-2606' then
  begin
    Label3.Caption := '___Ф___';
    Label4.Caption := 'den.ftl@gmail.com';
    Label5.Caption := '___С___';
    Label6.Caption := 'petroortep@gmail.com';
    Label7.Caption := '___Б___';
    Label8.Caption := 'bushkova.nastya@gmail.com';
    Edit.Clear;
    Edit.Enabled := False;
    bOk.Enabled := False;
    fMain.Activated := '180116052606';
  end
  else
    ShowMessage('Неправильний ключ!');
end;

procedure TfConnect.FormCreate(Sender: TObject);
begin
  if fMain.Activated = '180116052606' then
  begin
    Edit.Text := '1801-1605-2606';
    bOk.Click;
  end;
end;

end.

