#pragma once

#include <Automaton.h>

typedef bool ( *atm_command_cb_t )( int idx, int cmd );

class Atm_command : public Machine {
 public:
  Atm_command( void ) : Machine(){};

  atm_connector _oncommand;
  Stream* _stream;
  char* _buffer;
  int _bufsize, _bufptr;
  char _eol, _lastch;
  const char* _separator;
  const char* _commands;

  enum { IDLE, READCHAR, SEND };
  enum { EVT_INPUT, EVT_EOL, ELSE };
  enum { ACT_READCHAR, ACT_SEND };

  Atm_command& begin( Stream& stream, char buffer[], int size );
  Atm_command& trace( Stream& stream );
  int event( int id );
  void action( int id );
  Atm_command& onCommand( atm_command_cb_t callback, int idx = 0 );
  Atm_command& list( const char* cmds );

  Atm_command& separator( const char sep[] );
  int lookup( int id, const char* cmdlist );
  char* arg( int id );
};
