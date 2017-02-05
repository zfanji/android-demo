#pragma once
#include "ALLIRepoP.h"
#include "alli_event.h"
#include "alli_hash.h"
#include <unordered_map>
#include <unordered_set>

struct sqlite3_stmt;

namespace boost
{
	namespace signals2
	{
		class connection;
	}
	namespace filesystem
	{
		class path;
	}
}

namespace libgit2cpp
{
	class repository;
	class commit;
}

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIMonitorP;
	}
	namespace Helpers
	{
		class alli_event_args;
	}
	class ALLIEXTRepoP :
		public ALLIRepoP
	{
	public:
		typedef ALLIVaultCore::Helpers::alli_event::slot_type RepoFatalErrorSlotType;

		ALLIEXTRepoP();
		ALLIEXTRepoP(const ALLIVaultCore::ALLIEXTRepoP &src);
		~ALLIEXTRepoP();

		/**
		** Track working directory changes for an existing repo.
		** Return changed files in a dictionary. If the count of
		** of dictionary is zero, it means there are no changes.
		**/
		std::unordered_map<std::string, git_status_t> *trackWorkingDirectoryChanges();
		void set_hasInitialCommit(bool status);
		std::unordered_set<group_t> checkSharingGroupsForNM();
		boost::signals2::connection connectFatalError(const RepoFatalErrorSlotType &slot);
		void updateTotalBytesUsed();
		unsigned long long getTotalBytesUsed() const;

	protected:
		bool commitStagedFilesLocallyWithMessageEx(std::vector<std::string> &messages);
		bool stageFileWithRelativePath(const std::string &fileName);
		bool stageRemovedFileToIndex(const std::string &fileName);
		bool deleteEmptyParentDirectory(const boost::filesystem::path &srcPath);
		void open_input_file(FILE **input, const boost::filesystem::path &src);
		void open_output_file(FILE **output, const boost::filesystem::path &dest);
		void validate_dest(const boost::filesystem::path &dest);
		FILE *open_private_key_file(char **priKeyPath, int _ShFlag);
		boost::filesystem::path generateAESKeyFileName(const boost::filesystem::path &fileName, std::string &username);
		void monitorRepositoryP(const boost::filesystem::path &repoURL);

	private:
		boost::filesystem::path *groupDBURL;
		bool hasInitialCommit;
		bool switching;
		ALLIVaultCore::Engine::ALLIMonitorP *monitor;
		ALLIVaultCore::Helpers::alli_event RepoFatalError;
		std::unordered_set<group_t> sharingGroups;

		bool getLockForChangedFile(const boost::filesystem::path &fileName, int *fd);
		bool releaseLockForChangedFile(int *fd);
		std::string buildCommitMessage(std::vector<std::string> &messages);
		std::vector<std::shared_ptr<libgit2cpp::commit>> createParentsVector(libgit2cpp::repository &repo);
		void attachToEventHandlerForRepoFatalError();
		void processRepoFatalError(void *sender, ALLIVaultCore::Helpers::alli_event_args &e);
		void createSharingGroupDB();
		std::unordered_set<group_t> load_group_db(const boost::filesystem::path &groupDBURL);
		int extrepo_query_callback(sqlite3_stmt *sqlstmt);
		virtual void updateTotalBytesUsedImpl();
	};
}
