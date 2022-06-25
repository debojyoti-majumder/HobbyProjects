// Demo program write items to database

import mongoose from "mongoose";

const dbURI = "mongodb+srv://administrator:Admin123@cluster0.ozsgds8.mongodb.net/?retryWrites=true&w=majority";
mongoose.connect(dbURI)

const songSchema = mongoose.Schema({
        songTitle: String,
        songDurationMin: Number,
        songDurationSec: Number
    }
);

const SongModel = mongoose.model('Song',songSchema);

const song1 = new SongModel({
    songTitle: "Wish You Were Here",
    songDurationMin: 5,
    songDurationSec: 35,
});

const song2 = new SongModel({
    songTitle: "Have A Cigar",
    songDurationMin: 5,
    songDurationSec: 8,
});

const song3 = new SongModel({
    songTitle: "Shine On You Crazy Diamond",
    songDurationMin: 12,
    songDurationSec: 28,
});


song1.save((err,result) => {
    if( err ) return console.log(err)

    console.log(result);
});

try {
    let savedSong2 = await song2.save();
    console.log(`Saved song Id: ${savedSong2._id}`);

    let savedSong3 = await song3.save();
    console.log(`Saved song: ${savedSong3._id}`);
} 
catch( err ) {
    console.log(err);
}
