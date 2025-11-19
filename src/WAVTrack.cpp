#include "WAVTrack.h"
#include <iostream>

WAVTrack::WAVTrack(const std::string& title, const std::vector<std::string>& artists, 
                   int duration, int bpm, int sample_rate, int bit_depth)
    : AudioTrack(title, artists, duration, bpm), sample_rate(sample_rate), bit_depth(bit_depth) {

    std::cout << "WAVTrack created: " << sample_rate << "Hz/" << bit_depth << "bit" << std::endl;
}

// ========== TODO: STUDENTS IMPLEMENT THESE VIRTUAL FUNCTIONS ==========

void WAVTrack::load() {
    // TODO: Implement realistic WAV loading simulation
    // NOTE: Use exactly 2 spaces before the arrow (→) character
    std::cout<<"[WAVTrack::load] Loading WAV:\""<<title<<"\"at"<<sample_rate<<"Hz"<<bit_depth<<"bit(uncompressed)...\n";
    long long size = duration_seconds * sample_rate * (bit_depth / 8) * 2;
    std::cout<<"  ->Estimated file size:"<<size<< "bytes\n";
    std::cout<<"  ->Fast loading due to uncompressed format.\n";


}

void WAVTrack::analyze_beatgrid() {
    std::cout << "[WAVTrack::analyze_beatgrid] Analyzing beat grid for: \"" << title << "\"\n";
    double beats = (duration_seconds / 60.0) *bpm;
    const double PRECISION_FACTOR=1.0;
    std::cout<<"  ->Estimated beats: "<<beats<<"\n";
    std::cout<<"  ->Precision factor: "<<PRECISION_FACTOR<<" (uncompressed audio)\n";
    // TODO: Implement WAV-specific beat detection analysis
    // Requirements:
    // 1. Print analysis message with track title
    // 2. Calculate beats: (duration_seconds / 60.0) * bpm
    // 3. Print number of beats and mention uncompressed precision
    // should print "  → Estimated beats: <beats>  → Precision factor: 1.0 (uncompressed audio)"
}
    // TODO: Implement WAV quality scoring
    // NOTE: Use exactly 2 spaces before each arrow (→) character
    // NOTE: Cast beats to integer when printing
    double WAVTrack::get_quality_score() const {
    // (a) Start with a base score of 70 points
    double final_score = 70.0;

    // --- צבירת נקודות על סמך קצב דגימה (Sample Rate) ---
    
    // (c) Add 5 more points if sample_rate >= 96000 (high-res audio)
    // הערה: נבדוק את התנאי המחמיר יותר קודם כדי למנוע כפילות.
    if (sample_rate >= 96000) {
        final_score += 5.0; 
    } 
    // (b) Add 10 points if sample_rate >= 44100 (CD quality)
    // אם לא נכנס ל-96000, נבדוק את ה-44100 (שאינו נכלל בבדיקה הקודמת)
    else if (sample_rate >= 44100) {
        final_score += 10.0;
    }

    // --- צבירת נקודות על סמך עומק ביט (Bit Depth) ---

    // (e) Add 5 more points if bit_depth >= 24 (professional quality)
    if (bit_depth >= 24) {
        final_score += 5.0;
    }
    // (d) Add 10 points if bit_depth >= 16 (CD quality)
    // אם לא נכנס ל-24, נבדוק את ה-16
    else if (bit_depth >= 16) {
        final_score += 10.0;
    }

    // --- סיום ו-Clamp ---

    // (f) Cap maximum score at 100 points and return the final score
    if (final_score > 100.0) {
        final_score = 100.0;
    }
    
    return final_score;
}

    


PointerWrapper<AudioTrack> WAVTrack::clone() const {
    // TODO: Implement the clone method
   return PointerWrapper<AudioTrack>(new WAVTrack(*this));
}