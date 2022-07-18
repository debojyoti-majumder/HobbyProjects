use std::fs;

fn main() {
    let location_temp_day : u8 = 22;
    let location_temp_night : u8 = 18;

    let float_item = 10.4;
    
    println!("Float value : {} ", float_item);
    println!("Temperature in day {} " , location_temp_day);
    println!("Temp at night {}", location_temp_night);

    let avg = (location_temp_day + location_temp_night ) / 2;
    println!("Avg temp: {}", avg);

    let factional_value_1 = 10.0;
    let factional_value_2 = 3.0;
    let float_div = factional_value_1 / factional_value_2;
    println!("Should be a float value {} ", float_div);

    let avg_2 = ( location_temp_day as f64 + location_temp_night as f64 ) / 2.0;
    println!("Getting correct value: {}", avg_2);

    process_file();
}

fn process_file() {
    let file_content = fs::read_to_string("inp.txt");
    println!("{}", file_content.unwrap());
}
