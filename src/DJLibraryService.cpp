#include "DJLibraryService.h"
#include "SessionFileParser.h"
#include "MP3Track.h"
#include "WAVTrack.h"
#include <iostream>
#include <memory>
#include <filesystem>


DJLibraryService::DJLibraryService(const Playlist& playlist) 
    : playlist(playlist) {}
/**
 * @brief Load a playlist from track indices referencing the library
 * @param library_tracks Vector of track info from config
 */
DJLibraryService:: ~DJLibraryService(){
    for (AudioTrack* track : library) {
        delete track;
}
}
void DJLibraryService::buildLibrary(const std::vector<SessionConfig::TrackInfo>& library_tracks) {
    //Todo: Implement buildLibrary method
    for(size_t i=0;i<library_tracks.size();i++){
       SessionConfig::TrackInfo t=library_tracks[i];
        if(t.type=="MP3"){
            library.push_back(new MP3Track(t.title,t.artists, t.duration_seconds,t.bpm,t.extra_param1,t.extra_param2));
            std::cout<<"MP3: MP3Track created: "<<t.extra_param1<<"kbps\n";
        }
        else{
            library.push_back(new WAVTrack(t.title,t.artists, t.duration_seconds,t.bpm,t.extra_param1,t.extra_param2));
            std::cout<<"WAV: WAVTrack created: "<<t.extra_param1<<"Hz/"<<t.extra_param2<<"bit\n";
        }
    }
    std::cout<<"[INFO] Track library built: "<<library_tracks.size()<<"tracks loaded\n";
  }

/**
 * @brief Display the current state of the DJ library playlist
 * 
 */
void DJLibraryService::displayLibrary() const {
    std::cout << "=== DJ Library Playlist: " 
              << playlist.get_name() << " ===" << std::endl;

    if (playlist.is_empty()) {
        std::cout << "[INFO] Playlist is empty.\n";
        return;
    }

    // Let Playlist handle printing all track info
    playlist.display();

    std::cout << "Total duration: " << playlist.get_total_duration() << " seconds" << std::endl;
}

/**
 * @brief Get a reference to the current playlist
 * 
 * @return Playlist& 
 */
Playlist& DJLibraryService::getPlaylist() {
    // Your implementation here
    return playlist;
}

/**
 * TODO: Implement findTrack method
 * 
 * HINT: Leverage Playlist's find_track method
 */
AudioTrack* DJLibraryService::findTrack(const std::string& track_title) {
    return playlist.find_track(track_title);
}

void DJLibraryService::loadPlaylistFromIndices(const std::string& playlist_name, 
                                               const std::vector<int>& track_indices) {   
                                                        
    // Your implementation here
    int count=0;
    std::cout<<"Log: [INFO] Loading playlist: "<< playlist_name<<"\n";
    Playlist* p= new Playlist(playlist_name);
    for(size_t i=0;i<track_indices.size();i++){
        int casted=track_indices[i]-1;
        if(casted<0||casted>=library.size()){
            std::cout<<"[WARNING] Invalid track index:" <<casted;
        }
        else{
            AudioTrack* a=library[casted];
            PointerWrapper<AudioTrack> pw= a->clone(); //error in the clone() in classes
            AudioTrack* cloned=pw.get();
            cloned->load();
            cloned->analyze_beatgrid();
            playlist.add_track(cloned);
            std::cout<<"Added \""<<cloned->get_title()<<"\" to playlist \""<<playlist_name<<"\"\n";
            count++;


        }


    }
    std::cout<<"[INFO] Playlist loaded: \""<<playlist_name<<"("<<count<<" tracks)\n";

}
/**
 * TODO: Implement getTrackTitles method
 * @return Vector of track titles in the playlist
 */
std::vector<std::string> DJLibraryService::getTrackTitles() const {
    std::vector<std::string> titles;
    std::vector<AudioTrack*>tracks=playlist.getTracks();
    for(size_t i=0;i<tracks.size();i++){
        titles.push_back(tracks[i]->get_title());
    }
    return titles;
}
