use std::io;
use std::collections::HashMap;

// Main func
fn main()
{
    // Get mutable string variable from the string class
    // Mutable = changeable
    let mut input = String::new();

    // Loop to ensure that input is gotten
    while input.trim().is_empty()
    {
        // Prompt for name
        println!("Please enter the string: ");

        // Get the input from user and handle error
        io::stdin().read_line(&mut input)
            .expect("Failed to read line!");
    }

    let word_frequencies = word_freq(input);
    println!("{:?}", word_frequencies);
}

// Create a function which takes in a string as an argument, and returns a hashmap that uses
// strings for keys and usize for number of occurences.
fn word_freq(in_string: String) -> HashMap<String, usize>
{
    // Make it lowercase
    let new_string = in_string.trim().to_lowercase();

    // Get list of words split on whitespace
    let words = new_string.split_whitespace();

    // Create a mutable Hashmap for frequencies
    let mut word_frequency = HashMap::new();

    // Iterate through all the words
    for word in words
    {
        // Add word if not present, or increment if present
        *word_frequency.entry(word.to_string()).or_insert(0) += 1;
    }

    // Return
    return word_frequency;
}
