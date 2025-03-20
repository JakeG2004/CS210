fn main()
{
    let str1 = String::from("abcde");
    let str2 = String::from("edcba");

    if is_anagram(str1.clone(), str2.clone())
    {
        println!("{} and {} are anagrams", str1, str2);
    }

    else
    {
        println!("{} and {} are not anagrams", str1, str2);
    }
}

// Compare the two strings, removing character pairs.
fn is_anagram(str1: String, str2: String) -> bool
{
    // Ensure string lengths are the same
    if str1.len() != str2.len()
    {
        return false;
    }

    // Create vector of string 2 characters
    let mut str2_chars: Vec<char> = str2.chars().collect();

    // For each char in str1
    for cur_char in str1.chars()
    {
        // If the matching character is found in str2, strike it
        if let Some(pos) = str2_chars.iter().position(|&c2| c2 == cur_char)
        {
            str2_chars.remove(pos);
        }

        else
        {
            return false;
        }
    }

    // If all characters have been removed, the strings are anagrams
    return str2_chars.is_empty();
}