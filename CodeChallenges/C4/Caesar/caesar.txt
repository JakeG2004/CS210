/*
 * As a JJBA fan, obligatory SHEEEEEEEZZAHHHHHHHHH
*/

fn main()
{
    // No user input this time, just don't feel like it
    let plaintext = String::from("This is a string!");
    let shift = 2;

    // Get ciphertext form function
    let ciphertext = caesar_cipher(plaintext.to_lowercase(), shift);

    // Print result
    println!("The ciphertext of \"{}\" with shift {} is \"{}\"", plaintext, shift, ciphertext);
}

fn caesar_cipher(plaintext: String, shift: u8) -> String
{
    // Mutable string variable for ciphertext
    let mut ciphertext = String::from("");

    // Go through every character of plaintext
    for c in plaintext.chars()
    {
        // IF not alphabetic, add it to cipher and advance to next char
        if !c.is_alphabetic()
        {
            ciphertext.push(c);
            continue;
        }

        // Perform the shift
        let mut encrypted_char = (c as u8) + shift;

        // Wrap if needed
        if encrypted_char > ('z' as u8)
        {
            encrypted_char -= 26;
        }
        
        // Push onto string
        ciphertext.push(encrypted_char as char);
    }

    // Return ciphertext
    return ciphertext;
}