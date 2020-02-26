unit History;

interface

uses
  Classes, Controls, Forms,
  StdCtrls;

type
  TfHistory = class(TForm)
    lHist: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    bOk: TButton;
    procedure bOkClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fHistory: TfHistory;

implementation

{$R *.dfm}

procedure TfHistory.bOkClick(Sender: TObject);
begin
  Close;
end;

end.

