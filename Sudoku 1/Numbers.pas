unit Numbers;

interface

uses
  Classes, Controls, Forms,
  StdCtrls;

type
  TfNumbers = class(TForm)
    b_1: TButton;
    b_2: TButton;
    b_3: TButton;
    b_4: TButton;
    b_5: TButton;
    b_6: TButton;
    b_7: TButton;
    b_8: TButton;
    b_9: TButton;
    b_clear: TButton;
    b_close: TButton;
    procedure b_1Click(Sender: TObject);
    procedure b_2Click(Sender: TObject);
    procedure b_3Click(Sender: TObject);
    procedure b_4Click(Sender: TObject);
    procedure b_5Click(Sender: TObject);
    procedure b_6Click(Sender: TObject);
    procedure b_7Click(Sender: TObject);
    procedure b_8Click(Sender: TObject);
    procedure b_9Click(Sender: TObject);
    procedure b_clearClick(Sender: TObject);
    procedure b_closeClick(Sender: TObject);
  private
    { Private declarations }
  public
    Num: Char;
    { Public declarations }
  end;

var
  fNumbers: TfNumbers;
  Num: Char;

implementation

{$R *.dfm}

procedure TfNumbers.b_1Click(Sender: TObject);
begin
  Num := '1';
  Close;
end;

procedure TfNumbers.b_2Click(Sender: TObject);
begin
  Num := '2';
  Close;
end;

procedure TfNumbers.b_3Click(Sender: TObject);
begin
  Num := '3';
  Close;
end;

procedure TfNumbers.b_4Click(Sender: TObject);
begin
  Num := '4';
  Close;
end;

procedure TfNumbers.b_5Click(Sender: TObject);
begin
  Num := '5';
  Close;
end;

procedure TfNumbers.b_6Click(Sender: TObject);
begin
  Num := '6';
  Close;
end;

procedure TfNumbers.b_7Click(Sender: TObject);
begin
  Num := '7';
  Close;
end;

procedure TfNumbers.b_8Click(Sender: TObject);
begin
  Num := '8';
  Close;
end;

procedure TfNumbers.b_9Click(Sender: TObject);
begin
  Num := '9';
  Close;
end;

procedure TfNumbers.b_clearClick(Sender: TObject);
begin
  Num := '0';
  Close;
end;

procedure TfNumbers.b_closeClick(Sender: TObject);
begin
  Num := 'X';
  Close;
end;

end.

