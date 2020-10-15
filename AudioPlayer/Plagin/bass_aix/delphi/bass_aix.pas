unit BASS_AIX;
//Zavyalov Alexey Alexandrovich (RUS) (Завьялов Алексей Александрович)
//for more information please write on e-mail _ff_alex_ff_@mail.ru (RUS) (Все вопросы писать на e-mail _ff_alex_ff_@mail.ru)
interface
uses windows, bass;

const
 // BASS_CHANNELINFO type
 BASS_CTYPE_STREAM_AIX = $1F001; // Only for ADX of all versions (with AIXP support)

 // No TAG data
 bassaixdll = 'bass_aix.dll';

function BASS_AIX_StreamCreateFile(mem:BOOL; f:Pointer; offset,length:QWORD; flags:DWORD): HSTREAM; stdcall; external bassaixdll;
function BASS_AIX_StreamCreateURL(URL:PChar; offset:DWORD; flags:DWORD; proc:DOWNLOADPROC; user:Pointer): HSTREAM; stdcall; external bassaixdll;
function BASS_AIX_StreamCreateFileUser(system,flags:DWORD; var procs:BASS_FILEPROCS; user:Pointer): HSTREAM; stdcall; external bassaixdll;

implementation

end.
