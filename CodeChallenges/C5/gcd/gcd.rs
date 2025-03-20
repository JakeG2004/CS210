fn main()
{
    let gcd = my_gcd(13, 10);
    println!("{}", gcd);
}

// Euclidean extended algorithm
fn my_gcd(a: i32, b: i32) -> i32
{
    if a == 0
    {
        return b;
    }

    return my_gcd(b % a, a);
}