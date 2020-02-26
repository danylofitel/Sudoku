unit Rules;

interface

uses
  Classes, Controls, Forms,
  StdCtrls, ExtCtrls, jpeg;

type
  TfRules = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Image1: TImage;
    bOk: TButton;
    procedure bOkClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fRules: TfRules;

implementation

{$R *.dfm}

procedure TfRules.bOkClick(Sender: TObject);
begin
  Close;
end;

end.

