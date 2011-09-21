#include <iostream>
#include <QCoreApplication>
#include <QMetaObject>
#include <QMetaMethod>

#include <q2b/bind_qt_signal.hpp>
#include <boost/bind.hpp>

class Q : public QObject {
	Q_OBJECT
public:
	Q() : stopWork(false) { }

	void m1() {
		if (stopWork) return;
		for (;;) {
			emit m1Done();
			emit m1Failed(1);
			emit P2(2, 3);
		}	
	}

	void stop() {
		stopWork = true;
	}

private :
	bool stopWork;

signals:
	void m1Done();
	void m1Failed(int code);
	void P2(int x, int y);
};

class C {
public:
	explicit C(Q * q) : m_Q(q) {
		conn = bind_qt_signal<void(), qt_connection>(q, SIGNAL(m1Done()), 
					boost::bind(&C::onM1Done, this));

		conn1 = bind_qt_signal<void(int), qt_connection>(q, SIGNAL(m1Failed(int)),
					boost::bind(&C::onM1Failed, this, _1));

		conn2 = bind_qt_signal<void(int, int), qt_connection>(q, SIGNAL(P2(int,int)), 
					boost::bind(&C::onP2, this , _1 , _2));
		
		// Failed as expected!!!
		//bind_qt_signal<void(int,int,int,int,int,int,int,int,int), qt_connection>(q, SIGNAL(P2(int,int)),
		//			boost::bind(&C::failFunc, _1, _2 ,_3, _4, _5, _6, _7 , _8, _9))
	}

	void m1() {
		m_Q->m1();
	}

	void stop() {
		m_Q->stop();
	}

	void onM1Done() { 
		std::cout << __PRETTY_FUNCTION__ << std::endl; 
	}

	void onM1Failed(int x) {
		std::cout << __PRETTY_FUNCTION__ << " " << x << std::endl;
	}

	void onP2(int x, int y) {
		std::cout << __PRETTY_FUNCTION__ << " " << x << " " << y << std::endl; 
	}
	
	void failFunc(int,int,int,int,int,int,int,int,int) { }

	~C() {
		delete conn; delete conn1; delete conn2;
	}

private:
	Q * m_Q;

	qt_connection * conn;
	qt_connection * conn1;
	qt_connection * conn2;

};

int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);

	Q q; C c(&q);

	c.m1();
	sleep(10000);
	c.stop();

	return a.exec();
}

#include "many-signal-args.moc"

