#ifndef SERVICE_PROVIDER_H
#define SERVICE_PROVIDER_H

// Utility includes.
#include <map>

namespace Services
{
	/// <summary> Represents the type of service to get or set. </summary>
	enum ServiceType { Logger, Graphics, Controls, Screen, Events, Audio, Time, Particles };

	/// <summary> Represents a service provider which allows for services to be accessed. </summary>
	class ServiceProvider
	{
	public:
		ServiceProvider() : m_services() {}

		/// <summary> Gets the service with the given <see cref="ServiceType"/> and casts it to the given template variable. </summary>
		/// <param name="_serviceType"> The type of service to get. </param>
		/// <returns> The casted service. </returns>
		template <class T> T& GetService(const Services::ServiceType _serviceType)
		{
			// If the service does not exist, throw an error.
			if (m_services.count(_serviceType) == 0) { throw std::exception("Given service was not loaded."); }

			// Cast and return the service.
			return *static_cast<T*>(m_services.at(_serviceType));
		}

		/// <summary> Sets the service with the given <see cref="ServiceType"/> to the given service pointer. </summary>
		/// <param name="_service"> The pointer to the service to set. </param>
		/// <param name="_serviceType"> The type of service to set. </param>
		void SetService(void* _service, Services::ServiceType _serviceType)
		{
			// If the service has already been loaded, throw an error.
			if (m_services.count(_serviceType) != 0) { throw std::exception("Given service was already loaded."); }

			// Set the service.
			m_services.emplace(_serviceType, _service);
		}
	private:
		/// <summary> Holds pointers to services keyed by <see cref="ServiceType"/>. </summary>
		std::map<ServiceType, void*> m_services;
	};
}
#endif