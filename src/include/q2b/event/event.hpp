#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED

Q2B_NAMESPACE_BEGIN

template <typename Sink> class event_source;
template <typename Sink> class event_binder;

template <typename Sink> 
class event_binder {
public:
	typedef Sink sink_type;
	typedef event_source<sink_type> event_source_type;

	event_binder() : prev_(NULL), next_(NULL), sink_(sink_type()) 
		{ next_ = prev_ = this; }

	~event_binder() { unbind(); }

	void bind(event_source<sink_type> const & source, sink_type sink);
		
	inline void unbind() {
		prev_->next_ = next_;
		next_->prev_ = prev_;
		next_ = prev_ = this;
	}

private:		
	friend class event_source<sink_type>;
	event_binder * prev_;
	event_binder * next_;
	sink_type sink_;

	void attach_after(event_binder* what) {
		next_ = what->next_;
		next_->prev_ = this;
		what->next_ = this;
		prev_ = what;
	}

	event_binder(event_binder const &);
	event_binder & operator=(event_binder const&);
	
};

template <typename Sink> 
class event_source {
public:
	typedef Sink sink_type;
	typedef event_binder<sink_type> binder_type;

	event_source() : list_head_() { }

	inline void bind(binder_type & bndr, sink_type sink) {
		bndr.attach_after(&list_head_);
		bndr.sink = sink;
	}

	template <class Invoker>
	void emit(Invoker const & invoker) {
		binder_type * current = list_head_.next_;
		while (current != &list_head_) {
			if (current->sink_) {
				event_binder<sink_type> bookmark;
				bookmark.attach_after(current);
				// current may be excluded from list, but bookmark will always keep valid
				invoker(current->sink_); 	
				current = bookmark.next_;
				continue;
			}
			current = current->next_;
		}
	}

private:
	mutable binder_type list_head_;
	friend class event_binder<sink_type>;
			
	event_source(event_source const &);
	event_source& operator=(event_source const &);
	
};

template <typename Sink>
void event_binder<Sink>::bind(event_source<sink_type> const & source, sink_type sink) {
	unbind();
	attach_after(&source.list_head_);
	this->sink_ = sink;
}

Q2B_NAMESPACE_END

#endif

