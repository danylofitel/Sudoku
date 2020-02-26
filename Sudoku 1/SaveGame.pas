unit SaveGame;

interface

uses
  Classes, Controls, Forms,
  StdCtrls;

type
  TfSavePrevGame = class(TForm)
    lbl1: TLabel;
    btn_yes: TButton;
    btn_no: TButton;
    procedure btn_yesClick(Sender: TObject);
    procedure btn_noClick(Sender: TObject);
  private
    { Private declarations }
  public
    SaveChoice: Boolean;
    { Public declarations }
  end;

var
  fSavePrevGame: TfSavePrevGame;
  SaveChoice: Boolean;

implementation

{$R *.dfm}

procedure TfSavePrevGame.btn_yesClick(Sender: TObject);
begin
  SaveChoice := True;
  Close;
end;

procedure TfSavePrevGame.btn_noClick(Sender: TObject);
begin
  SaveChoice := False;
  Close;
end;

end.

