#include "irrKlang.h"

namespace irrklang
{
	class IAudioStreamLoader;
	struct SInternalAudioInterface;

	
	class ISoundEngine : public virtual irrklang::IRefCounted
	{
	public:

		
		virtual const char* getDriverName() = 0;

		virtual ISound* play2D(const char* soundFileName,
			bool playLooped = false,
			bool startPaused = false,
			bool track = false,
			E_STREAM_MODE streamMode = ESM_AUTO_DETECT,
			bool enableSoundEffects = false) = 0;

	
		virtual ISound* play2D(ISoundSource* source,
			bool playLooped = false,
			bool startPaused = false,
			bool track = false,
			bool enableSoundEffects = false) = 0;

		virtual ISound* play3D(const char* soundFileName, vec3df pos,
			bool playLooped = false,
			bool startPaused = false,
			bool track = false,
			E_STREAM_MODE streamMode = ESM_AUTO_DETECT,
			bool enableSoundEffects = false) = 0;

		
		virtual ISound* play3D(ISoundSource* source, vec3df pos,
			bool playLooped = false,
			bool startPaused = false,
			bool track = false,
			bool enableSoundEffects = false) = 0;

		//! Stops all currently playing sounds.
		virtual void stopAllSounds() = 0;

		//! Pauses or unpauses all currently playing sounds.
		virtual void setAllSoundsPaused(bool bPaused = true) = 0;

		virtual ISoundSource* getSoundSource(const ik_c8* soundName, bool addIfNotFound = true) = 0;

		
		virtual ISoundSource* getSoundSource(ik_s32 index) = 0;

		//! Returns amount of loaded sound sources.
		virtual ik_s32 getSoundSourceCount() = 0;

		
		virtual ISoundSource* addSoundSourceFromFile(const ik_c8* fileName, E_STREAM_MODE mode = ESM_AUTO_DETECT,
			bool preload = false) = 0;

		
		virtual ISoundSource* addSoundSourceFromMemory(void* memory, ik_s32 sizeInBytes, const ik_c8* soundName,
			bool copyMemory = true) = 0;


		
		virtual ISoundSource* addSoundSourceFromPCMData(void* memory, ik_s32 sizeInBytes,
			const ik_c8* soundName, SAudioStreamFormat format,
			bool copyMemory = true) = 0;

		
		virtual ISoundSource* addSoundSourceAlias(ISoundSource* baseSource, const ik_c8* soundName) = 0;

		
		virtual void removeSoundSource(ISoundSource* source) = 0;

		
		virtual void removeSoundSource(const ik_c8* name) = 0;

		
		virtual void removeAllSoundSources() = 0;

		
		virtual void setSoundVolume(ik_f32 volume) = 0;

	
		virtual ik_f32 getSoundVolume() = 0;

		
		virtual void setListenerPosition(const vec3df& pos,
			const vec3df& lookdir,
			const vec3df& velPerSecond = vec3df(0, 0, 0),
			const vec3df& upVector = vec3df(0, 1, 0)) = 0;
	
		virtual void update() = 0;

		//! Returns if a sound with the specified name is currently playing.
		virtual bool isCurrentlyPlaying(const char* soundName) = 0;

		//! Returns if a sound with the specified source is currently playing.
		virtual bool isCurrentlyPlaying(ISoundSource* source) = 0;

		
		virtual void registerAudioStreamLoader(IAudioStreamLoader* loader) = 0;

		//! Returns if irrKlang is running in the same thread as the application or is using multithreading.
		/** This basicly returns the flag set by the user when creating the sound engine.*/
		virtual bool isMultiThreaded() const = 0;

		//! Adds a file factory to the sound engine, making it possible to override file access of the sound engine.
		/** Derive your own class from IFileFactory, overwrite the createFileReader()
		method and return your own implemented IFileReader to overwrite file access of irrKlang. */
		virtual void addFileFactory(IFileFactory* fileFactory) = 0;

		
		virtual void setDefault3DSoundMinDistance(ik_f32 minDistance) = 0;

		
		virtual ik_f32 getDefault3DSoundMinDistance() = 0;

		
		virtual void setDefault3DSoundMaxDistance(ik_f32 maxDistance) = 0;

		
		virtual ik_f32 getDefault3DSoundMaxDistance() = 0;

	
		virtual void setRolloffFactor(ik_f32 rolloff) = 0;

		
		virtual void setDopplerEffectParameters(ik_f32 dopplerFactor = 1.0f, ik_f32 distanceFactor = 1.0f) = 0;

		
		virtual bool loadPlugins(const ik_c8* path) = 0;

		
		virtual const SInternalAudioInterface& getInternalAudioInterface() = 0;

		
		virtual bool setMixedDataOutputReceiver(ISoundMixedOutputReceiver* receiver) = 0;
	};


	
	struct SInternalAudioInterface
	{
		//! IDirectSound interface, this is not null when using the ESOD_DIRECT_SOUND audio driver
		void* pIDirectSound;

		//! IDirectSound8 interface, this is not null when using the ESOD_DIRECT_SOUND8 audio driver
		void* pIDirectSound8;

		//! HWaveout interface, this is not null when using the ESOD_WIN_MM audio driver
		void* pWinMM_HWaveOut;

		//! ALSA PCM Handle interface, this is not null when using the ESOD_ALSA audio driver
		void* pALSA_SND_PCM;

		//! AudioDeviceID handle, this is not null when using the ESOD_CORE_AUDIO audio driver
		ik_u32 pCoreAudioDeciceID;
	};



} // end namespace irrklang


