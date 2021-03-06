var regkey:HKEY;

procedure OpenReg();
begin
RegCreateKeyEx(HKEY_CURRENT_USER,
PChar('SoftWare\ax_midi_player'),
0,nil,0,KEY_ALL_ACCESS,nil,regkey,nil);
end;

procedure CloseReg();
begin
RegCloseKey(regkey);
end;

procedure GetKeySW(kname:ansistring;var s:unicodestring);
var regtype:longword=REG_SZ;
var ca:array[0..$100*2-1]of byte;
var size:longword=$100*2;
begin
if RegQueryValueExW(regkey,PWChar(unicodestring(kname)),nil,@regtype,@ca,@size)=ERROR_SUCCESS then
  s:=copy(UnicodeString(pwchar(@ca)),0,length(unicodestring(pwchar(@ca))));
end;

procedure GetKeyS(kname:ansistring;var s:ansistring);
var regtype:longword=REG_SZ;
var ca:array[0..$100-1]of byte;
var size:longword=$100;
begin
if RegQueryValueEx(regkey,PChar(kname),nil,@regtype,@ca,@size)=ERROR_SUCCESS then
  s:=PChar(@ca);
end;

procedure GetKeyI(kname:ansistring;var i:longword);
var regtype:longword=REG_DWORD;
var ca:array[0..3] of byte;
var size:longword=4;
begin
if RegQueryValueEx(regkey,PChar(kname),nil,@regtype,@ca,@size)=ERROR_SUCCESS then
  i:=ca[3] shl 24 or ca[2] shl 16 or ca[1] shl 8 or ca[0]
end;

procedure SetKeySW(kname:ansistring;s:unicodestring);
begin
RegSetValueExW(regkey,PWChar(UnicodeString(kname)),0,REG_SZ,PWChar(s),length(s)*2);
end;

procedure SetKeyS(kname:ansistring;s:ansistring);
begin
RegSetValueEx(regkey,PChar(kname),0,REG_SZ,PChar(s),length(PChar(s)));
end;

procedure SetKeyI(kname:ansistring;i:longword);
begin
RegSetValueEx(regkey,PChar(kname),0,REG_DWORD,@i,sizeof(DWORD));
end;

var rs:ansistring;
var fnames:unicodestring;
var framerate:longword;
var loop:longword;
var miditime:longword;
var midipos:longword;
var voli:longword;
var kbdcb:longword;
var kchb:longword=0;
var kchb2:longword=0;
var para:unicodestring;
var parai:longword;
var fdir:unicodestring;
var hwm:longword;
const mult0=600;
var mult:longword;
var autofresh:longword;
var midiOuti:longword;
var msgbufn0:longword;
var kchord0:longword;
var kkey0:longint;
var kmessure:longword;
var msgvol0:longword;
var maxkbdc:longword;
var helpb:longword;

procedure ResetReg();
begin
fnames:='midiplayer by ax_pokl';
framerate:=120;
miditime:=0;
midipos:=0;
voli:=0;
loop:=1;
kbdcb:=0;
kchb:=0;
kchb2:=0;
mult:=100;
autofresh:=0;
midiouti:=0;
msgbufn0:=128;
kchord0:=0;
kkey0:=0;
kmessure:=0;
msgvol0:=2;
maxkbdc:=$40;
helpb:=0;
end;

procedure SaveReg();
begin
SetKeySW('fnames',fnames);
SetKeyI('framerate',framerate);
SetKeyI('midipos',miditime);
SetKeyI('voli',voli);
SetKeyI('loop',loop);
SetKeyI('kbdcb',kbdcb);
SetKeyI('kchb',kchb);
SetKeyI('kchb2',kchb2);
SetKeyI('mult',mult);
SetKeyI('autofresh',autofresh);
SetKeyI('midiouti',midiouti);
SetKeyI('framerate',framerate);
SetKeyI('msgbufn0',msgbufn0);
SetKeyI('kmessure',kmessure);
SetKeyI('msgvol0',msgvol0);
SetKeyI('maxkbdc',maxkbdc);
SetKeyI('helpb',helpb);
end;

procedure LoadReg();
begin
GetKeySW('fnames',fnames);
GetKeyI('framerate',framerate);
GetKeyI('midipos',midipos);
GetKeyI('voli',voli);
GetKeyI('loop',loop);
GetKeyI('kbdcb',kbdcb);
GetKeyI('kchb',kchb);
GetKeyI('kchb2',kchb2);
GetKeyI('mult',mult);
GetKeyI('autofresh',autofresh);
GetKeyI('midiouti',midiouti);
GetKeyI('framerate',framerate);
GetKeyI('msgbufn0',msgbufn0);
GetKeyI('kmessure',kmessure);
GetKeyI('msgvol0',msgvol0);
GetKeyI('maxkbdc',maxkbdc);
GetKeyI('helpb',helpb);
end;
