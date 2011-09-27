#include <typeinfo>
#include <iostream>

#include <QCoreApplication>
#include <QMetaObject>
#include <QMetaMethod>

#include <q2b/qt_signals.hpp>
#include <boost/bind.hpp>

static size_t abstract_clazz_dtor_called = 0;

struct abstract_clazz {
	virtual void call() const = 0;
	virtual int get_int() const = 0;
	virtual void set_int(int) = 0;

	virtual ~abstract_clazz() { ++abstract_clazz_dtor_called; } 	
};

struct derived_clazz : public abstract_clazz {	
	virtual void call() const {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	virtual int get_int() const { return var_; }
	virtual void set_int(int var) { var_ = var;  }

private :
	int var_;

};

class qt_emit_source_clazz : public QObject { 
	Q_OBJECT 
public :
	void start() {
		static int count = 0;
		abstract_clazz * a = NULL; 
		(a = new derived_clazz)->set_int(count++);
		emit do_some(a);
	}	

signals :
	void do_some(abstract_clazz *);

};

class recv_clazz {
public :
	void set_qsource(qt_emit_source_clazz * q) {
		bind_qt_signal<void(abstract_clazz *)>(
				q, SIGNAL(do_some(abstract_clazz *)), boost::bind(&recv_clazz::recv, this, _1));
	}
	
private :	
	void recv(abstract_clazz * v) {
		v->call();	
		std::cout << typeid(v).name() << " : " << v->get_int() << std::endl;
		delete v; v = NULL;
	}

};

int main(int ac, char ** av) {
	QCoreApplication a(ac, av);
	
	qt_emit_source_clazz q_emit_clazz;
	recv_clazz c_recv;
	
	c_recv.set_qsource(&q_emit_clazz);
	
	for (size_t i = 0; i < 100000; ++i)
		q_emit_clazz.start();
	std::cout << "abstract_clazz_dtor_called" << abstract_clazz_dtor_called << std::endl;
	return a.exec();
}

#include "polymorphic.moc"
