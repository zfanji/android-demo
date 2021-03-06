#pragma once
#include "alli_event_args.h"
#include <unordered_map>

namespace ALLIVaultCore
{
	enum class ALLIRepoTypeP;
	enum class ALLIActionDirectionP;
	enum class ALLIChangeStatusP;
	class latest_update_event_args :
		public Helpers::alli_event_args
	{
	public:
		ALLIVaultCore::ALLIRepoTypeP repoType;
		ALLIVaultCore::ALLIActionDirectionP actDir;
		std::string hostUserName;
		std::string groupName;
		std::chrono::system_clock::time_point evtTime;
		std::string sender;
		std::string recipient;
		std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> changeSet;

		latest_update_event_args();
		~latest_update_event_args();

	private:
		std::string to_string_impl() const override;
	};
}

