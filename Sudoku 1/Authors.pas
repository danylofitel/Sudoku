unit Authors;

interface

uses
  Classes, Controls, Forms,
  StdCtrls, ExtCtrls, jpeg;

type
  TfAuthors = class(TForm)
    Label1: TLabel;
    Image: TImage;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Button1: TButton;
    Image1: TImage;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fAuthors: TfAuthors;

implementation

uses Connect;

{$R *.dfm}

procedure TfAuthors.Button1Click(Sender: TObject);
begin
  fConnect.ShowModal;
end;

end.

