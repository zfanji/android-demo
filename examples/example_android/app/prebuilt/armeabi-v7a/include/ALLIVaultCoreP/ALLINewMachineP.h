/*
* Copyright (C) ALLI Enterprises, Inc. ALL rights reserved.
*
* This file is part of ALLIVault. For full terms see the included
* COPYING file.
*/
#pragma once
#include "alli_common.h"
#include "ALLIUserP.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class transfer_progress_event_args;
	}
	namespace FrontEnd
	{
		class ALLIExistingUserP;
		/**
		* Class ALLINewMachineP. It handles all operations related to
		* syncing data to a new machine.
		*/
		class ALLINewMachineP :
			public ALLIUserP
		{
		public:
			/**
			 * Function pointer for init DB for sync folder.
			 */
			void(*init_db_fn_ptr)();
			typedef std::function<void()> InitializeDBForSyncFolderCallback;
			void connectInitializeDBForSyncFolder(InitializeDBForSyncFolderCallback cb);
			/**
			 * Function pointer for init DB for mainbox.
			 */
			void(*init_db_mb_fn_ptr)();
			/**
			 * Function pointer to pass username.
			 *
			 * @param a string object
			 */
			void(*pass_uname_fn_ptr)(const std::string &);
			typedef std::function<bool(const std::string &, const boost::filesystem::path &, void *)> DownloadOneFileExCallback;
			/**
			 * Function pointer to download a file for sync folder.
			 *
			 * @param src a string object indicating the source of the file
			 * @param dest a boost filesystem path object identifying the destination of the file
			 * @param a void pointer to the calling object
			 */
			ALLIVAULTCOREP_API void connectDownloadOneFileEx(DownloadOneFileExCallback cb);
			/**
			 * Function pointer to report new machine sync progress.
			 *
			 * @param a void pointer to the calling object
			 * @param a new_machine_event_args object containing payload about the progress
			 */
			void(*slot_callback_new_machine)(void *, ALLIVaultCore::FrontEnd::new_machine_event_args &);
			/**
			 * Function pointer to a mailbox friend.
			 */
			bool(*mb_friend_fn_ptr)();
			typedef std::function<void()> UpdateTotalBytesCallback;
			/**
			 * Function pointer to update total bytes used by sync folder.
			 */
			void(*update_total_bytes_fn_ptr)();
			ALLIVAULTCOREP_API void connectUpdateTotalBytesSync(UpdateTotalBytesCallback cb);
			/**
			 * Function pointer to update total bytes used by mailbox.
			 */
			void(*update_total_bytes_mb_fn_ptr)();
			ALLIVAULTCOREP_API void connectUpdateTotalBytesMB(UpdateTotalBytesCallback cb);
			/**
			* Function pointer to download a file for mailbox.
			*
			* @param src a string object indicating the source of the file
			* @param dest a boost filesystem path object identifying the destination of the file
			* @param src_key a string object indicating the key for the source file
			* @param dest_key a boost filesystem path object identifying the key for the destination file
			* @param a void pointer to the calling object
			*/
			bool(*downloadOneFilePairExPtr) (const std::string &src, const boost::filesystem::path &dest, const std::string &src_key, const boost::filesystem::path &dest_key, void *caller);
			/**
			 * Flag indicating whether mailbox exists.
			 */
			bool nm_mbexists;

			/**
			* Class constructor. Create an ALLINewMachineP object.
			*
			* @param slot_callback a function pointer to report file download progress
			*/
			ALLIVAULTCOREP_API explicit ALLINewMachineP(void(*slot_callback)(void *, ALLIVaultCore::Helpers::transfer_progress_event_args &));
			/**
			* Class copy constructor.
			*
			* @param src a const reference to an ALLINewMachineP object
			*/
			ALLINewMachineP(const ALLIVaultCore::FrontEnd::ALLINewMachineP &src);
			/**
			* Class destructor.
			*/
			ALLIVAULTCOREP_API ~ALLINewMachineP();

			/**
			 * Check if the username and password match the records on the server.
			 *
			 * @param username username for the account to sync a new machine
			 * @param passwd password for the account
			 * @param dbTimeout a flag set to true if the connection timed out
			 */
			ALLIVAULTCOREP_API bool userPasswordMatch(const std::string &username, const std::string &passwd, bool &dbTimeout);
			/**
			 * Set URI on the server for the sync folder.
			 */
			ALLIVAULTCOREP_API void openServerRepositoryForEncryptedRepo();
			/**
			 * Set URI on the server for the mailbox.
			 */
			ALLIVAULTCOREP_API void openServerRepositoryForMBEncryptedRepo();
			/**
			 * Operations to actually sync all contents of a user to a local machine.
			 */
			ALLIVAULTCOREP_API void openServerRepositories();
			/**
			* Import a key-pair from a designated source
			*
			* @param keyDir the folder where the key-pair source is located
			* @return true on success, false otherwise
			*/
			ALLIVAULTCOREP_API bool importKeyPair(const boost::filesystem::path &keyDir);
			ALLIVAULTCOREP_API void batchActionsForNewMachine();
			ALLIVAULTCOREP_API void setExistingUser(ALLIVaultCore::FrontEnd::ALLIExistingUserP &eu);

		private:
			class ALLINewMachineP_impl;
			std::unique_ptr<ALLINewMachineP_impl> pimpl;
		};
	}
}

