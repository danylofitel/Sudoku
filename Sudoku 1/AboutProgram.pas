unit AboutProgram;

interface

uses
  Classes, Controls, Forms,
  StdCtrls;

type
  TfAboutProgram = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fAboutProgram: TfAboutProgram;

implementation

{$R *.dfm}

procedure TfAboutProgram.Button1Click(Sender: TObject);
begin
  Close;
end;

end.

