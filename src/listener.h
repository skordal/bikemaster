// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef LISTENER_H
#define LISTENER_H

class Listener
{
	public:
		Listener * getNext() const { return next; }
		void setNext(Listener * next) { this->next = next; }

	private:
		Listener * next;
};

template<typename T>
class Listenable
{
	public:
		void addListener(T * listener)
		{
			listener->setNext(listeners);
			listeners = listener;
		}

		void removeListener(T * listener)
		{
			T * prev = nullptr, * current = listeners;
			while(current != nullptr)
			{
				if(current == listener)
				{
					if(prev != nullptr)
						prev->setNext(current->getNext());
					break;
				}
			}
		}
	protected:
		Listenable() : listeners(nullptr) {}
		T * getListeners() const { return listeners; }
	private:
		T * listeners;
};

#endif
