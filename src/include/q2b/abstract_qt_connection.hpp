#ifndef ABSTRACT_QT_CONNECTION_HPP_INCLUDED
#define ABSTRACT_QT_CONNECTION_HPP_INCLUDED

#include <string>

class abstract_qt_connection {
public :
	abstract_qt_connection() { }
	virtual ~abstract_qt_connection() { }
	
	virtual void set_name(std::string const & name) = 0;
	virtual std::string get_name() const = 0;
	virtual std::string get_id() const = 0;
	
	virtual int get_slot_idx() const = 0;
	virtual int get_signal_idx() const = 0;

	virtual void connect() = 0;		
	virtual void disconnect() = 0;
	virtual bool is_connected() const = 0;

protected :
	virtual void set_connect_state(bool state) = 0;

	abstract_qt_connection(abstract_qt_connection const &);
	abstract_qt_connection & operator=(abstract_qt_connection const &);
};

#endif

