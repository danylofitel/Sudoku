unit AboutGame;

interface

uses
  Classes, Controls, Forms,
  ExtCtrls, StdCtrls, jpeg;

type
  TfAboutGame = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    bHistory: TButton;
    bRules: TButton;
    Image1: TImage;
    btnOK: TButton;
    procedure bHistoryClick(Sender: TObject);
    procedure bRulesClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fAboutGame: TfAboutGame;

implementation

uses History, Rules;

{$R *.dfm}

procedure TfAboutGame.bHistoryClick(Sender: TObject);
begin
  fHistory.ShowModal;
end;

procedure TfAboutGame.bRulesClick(Sender: TObject);
begin
  fRules.ShowModal;
end;

procedure TfAboutGame.btnOKClick(Sender: TObject);
begin
  Close;
end;

end.

