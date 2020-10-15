unit BASS_ADX;
//Zavyalov Alexey Alexandrovich (RUS) (Завьялов Алексей Александрович)
//for more information please write on e-mail _ff_alex_ff_@mail.ru (RUS) (Все вопросы писать на e-mail _ff_alex_ff_@mail.ru)
interface
uses windows, bass;

const
 // BASS_CHANNELINFO type
 BASS_CTYPE_STREAM_ADX = $1F000; // ADX stream type (not splitted on version 3 or 4 or 5)

 // ADX Loop TAG
 BASS_TAG_ADX_LOOP     = $12000; // ADX loop structure
 bassadxdll = 'bass_adx.dll';

type
 TADX_LoopStruct = record
 LoopEnabled : BOOL;
 SampleStart : QWORD;
 ByteStart : QWORD;
 SampleEnd : QWORD;
 ByteEnd : QWORD;
 end;

type
 PADX_LoopStruct = ^TADX_LoopStruct;

function BASS_ADX_StreamCreateFile(mem:BOOL; f:Pointer; offset,length:QWORD; flags:DWORD): HSTREAM; stdcall; external bassadxdll;
function BASS_ADX_StreamCreateURL(URL:PChar; offset:DWORD; flags:DWORD; proc:DOWNLOADPROC; user:Pointer): HSTREAM; stdcall; external bassadxdll;
function BASS_ADX_StreamCreateFileUser(system,flags:DWORD; var procs:BASS_FILEPROCS; user:Pointer): HSTREAM; stdcall; external bassadxdll;

implementation

end.
