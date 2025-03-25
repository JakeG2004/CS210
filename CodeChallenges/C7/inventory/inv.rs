use std::collections::HashMap;
use std::io;
use std::cmp::max;
use std::process;

fn main()
{
    // Create the hashmap
    let mut inventory: HashMap<String, i32> = HashMap::new();

    println!("Welcome to Jake's Inventory System!");

    let stdin = io::stdin();
    let mut input = String::new();

    loop
    {
        // Priint menu
        println!("\n\n=====Options=====");
        println!("1. Add Item");
        println!("2. Remove Item");
        println!("3. List Inventory");
        println!("4. Exit");

        // Get user input
        input.clear();
        if stdin.read_line(&mut input).is_err() {
            println!("Failed to read input.");
            return;
        }
        let choice: i32 = match input.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Invalid number. Please enter a valid integer.");
                return;
            }
        };

        if choice < 1 || choice > 4
        {
            println!("Invalid choice!");
            continue;
        }

        match choice
        {
            1 => add_item(&mut inventory),
            2 => remove_item(&mut inventory),
            3 => show_inventory(inventory.clone()),
            4 => process::exit(0),
            _ => println!("Invaliid!")
        }
    }
}

fn show_inventory(inventory: HashMap<String, i32>)
{
    println!("\n\n=====Inventory=====");
    for (key, value) in inventory.clone().into_iter()
    {
        println!("{}, {}", key, value);
    }
}

fn add_item(inventory: &mut HashMap<String, i32>)
{
    println!("\n\n=====Add Item=====");
    let stdin = io::stdin();
    let mut input = String::new();

    // Get item name
    println!("Enter item name:");
    input.clear();
    if stdin.read_line(&mut input).is_err() {
        println!("Failed to read item name.");
        return;
    }
    let item_name = input.trim().to_string();

    // Get item amount
    println!("Enter item amount:");
    input.clear();
    if stdin.read_line(&mut input).is_err() {
        println!("Failed to read item amount.");
        return;
    }
    let amount: i32 = match input.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Invalid number. Please enter a valid integer.");
            return;
        }
    };

    // If it exists, add the amount
    if inventory.get(&item_name).is_some()
    {
        inventory.insert(item_name.clone(), inventory[&item_name] + amount);
        return;
    }

    // If doesn't exist, insert
    inventory.entry(item_name).or_insert(amount);
}

fn remove_item(inventory: &mut HashMap<String, i32>)
{
    println!("\n\n=====Remove Item=====");
    let stdin = io::stdin();
    let mut input = String::new();

    // Get item name
    println!("Enter item name:");
    input.clear();
    if stdin.read_line(&mut input).is_err() {
        println!("Failed to read item name.");
        return;
    }
    let item_name = input.trim().to_string();

    // Get item amount
    println!("Enter item amount:");
    input.clear();
    if stdin.read_line(&mut input).is_err() {
        println!("Failed to read item amount.");
        return;
    }
    let amount: i32 = match input.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Invalid number. Please enter a valid integer.");
            return;
        }
    };

    // If it exists, add the amount
    if inventory.get(&item_name).is_some()
    {
        if max(inventory[&item_name] - amount, 0) == 0
        {
            inventory.remove(&item_name);
            return;
        }
        inventory.insert(item_name.clone(), max(inventory[&item_name] - amount, 0));
        return;
    }

    println!("{} doesn't exist in the inventory", item_name);
}