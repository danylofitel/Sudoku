program Sudoku;

uses
  Forms,
  Main in 'Main.pas' {fMain},
  AboutGame in 'AboutGame.pas' {fAboutGame},
  History in 'History.pas' {fHistory},
  Rules in 'Rules.pas' {fRules},
  Numbers in 'Numbers.pas' {fNumbers},
  AboutProgram in 'AboutProgram.pas' {fAboutProgram},
  Authors in 'Authors.pas' {fAuthors},
  Connect in 'Connect.pas' {fConnect},
  SaveGame in 'SaveGame.pas' {fSavePrevGame};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'Судоку';
  Application.CreateForm(TfMain, fMain);
  Application.CreateForm(TfAboutGame, fAboutGame);
  Application.CreateForm(TfHistory, fHistory);
  Application.CreateForm(TfRules, fRules);
  Application.CreateForm(TfNumbers, fNumbers);
  Application.CreateForm(TfAboutProgram, fAboutProgram);
  Application.CreateForm(TfAuthors, fAuthors);
  Application.CreateForm(TfConnect, fConnect);
  Application.CreateForm(TfSavePrevGame, fSavePrevGame);
  Application.Run;
end.

