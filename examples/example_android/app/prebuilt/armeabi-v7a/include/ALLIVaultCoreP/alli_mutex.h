#pragma once

#include "alli_common.h"


namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_mutex
		{
		public:
			ALLIVAULTCOREP_API alli_mutex(void);
			alli_mutex(ALLIVaultCore::Helpers::alli_mutex const &src) = delete;
			alli_mutex &operator=(ALLIVaultCore::Helpers::alli_mutex const &src) = delete;
			ALLIVAULTCOREP_API ~alli_mutex(void);
			ALLIVAULTCOREP_API bool WaitOne();
			void lock();
			ALLIVAULTCOREP_API bool TryWaitOne();
			ALLIVAULTCOREP_API void ReleaseMutex();
			void unlock();

		private:
			class alli_mutex_impl;
			std::unique_ptr<alli_mutex_impl> pimpl;
		};
	}
}
