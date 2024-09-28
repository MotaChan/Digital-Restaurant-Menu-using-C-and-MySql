delete from Category;
delete from Origin;
delete from Dish;
delete from DishOrigin;
delete from DishIngredient;
delete from Ingredient;
INSERT INTO Category (CategoryID, CategoryName) VALUES (1, 'Dessert'), (2, 'Main Dish'), (3, 'Snack');

INSERT INTO Origin (OriginID, OriginName) VALUES 
    (1, 'Vietnam'),
    (2, 'Japan'),
    (3, 'Korea'),
    (4, 'China'),
    (5, 'America');

INSERT INTO Ingredient (IngredientID, IngredientName, CountingUnit, Quantity, ImportDate, ExpiredDate) 
VALUES 
    (1, 'Beef', 'gram', 500, '2024-01-01', '2024-06-30'),
    (2, 'Rice Noodles', 'gram', 200, '2024-01-15', '2024-12-31'),
    (3, 'Fish', 'gram', 300, '2024-01-20', '2024-12-31'),
    (4, 'Duck', 'gram', 400, '2024-02-01', '2024-08-31'),
    (6, 'Pork', 'gram', 300, '2024-03-01', '2024-09-01'),
    (7, 'Baguette', 'piece', 5, '2024-03-15', '2024-09-15'),
    (8, 'Ramen Noodles', 'gram', 250, '2024-04-01', '2024-10-01'),
    (9, 'Kimchi', 'gram', 150, '2024-05-01', '2024-11-01'),
    (10, 'Cheese', 'gram', 100, '2024-06-01', '2024-12-01'),
    (11, 'Rice', 'gram', 300, '2024-06-10', '2024-12-10'),
    (12, 'Bun', 'piece', 3, '2024-06-15', '2024-12-15');

INSERT INTO Dish (DishID, DishName, Price, Availability, TimeAvailability, CategoryID) 
VALUES 
    (1, 'Pho', 10.99, 1, '12:00:00', 2),
    (2, 'Sushi Sashimi', 22.99, 1, '18:00:00', 2),
    (3, 'Bibimbap', 15.99, 1, '13:30:00', 2),
    (4, 'Peking Duck', 18.99, 1, '20:00:00', 2),
    (5, 'Hamburger', 12.99, 1, '11:00:00', 2),
    (6, 'Banh Mi', 8.99, 1, '14:00:00', 3),
    (7, 'Ramen', 14.99, 1, '19:30:00', 2),
    (8, 'Kimchi Fried Rice', 13.99, 1, '12:45:00', 2),
    (9, 'Hot and Sour Soup', 11.99, 1, '14:15:00', 2),
    (10, 'Philly Cheesesteak', 16.99, 1, '21:00:00', 2);

INSERT INTO DishOrigin (DishID, OriginID) VALUES
    (1, 1), -- Pho - Vietnam
    (2, 2), -- Sushi Sashimi - Japan
    (3, 3), -- Bibimbap - Korea
    (4, 4), -- Peking Duck - China
    (5, 5), -- Hamburger - America
    (6, 1), -- Banh Mi - Vietnam
    (7, 2), -- Ramen - Japan
    (8, 3), -- Kimchi Fried Rice - Korea
    (9, 4), -- Hot and Sour Soup - China
    (10, 5); -- Philly Cheesesteak - America

INSERT INTO DishIngredient (DishID, IngredientID) VALUES
    (1, 1), -- Pho - Beef
    (1, 2), -- Pho - Rice Noodles
    (2, 3), -- Sushi Sashimi - Fish
    (2, 11), -- Sushi Sashimi - Rice  
    (3, 6), -- Bibimbap - Pork
    (3, 11), -- Bibimbap - Rice  
    (4, 4), -- Peking Duck - Duck
    (5, 1), -- Hamburger - Beef  
    (5, 12), -- Hamburger - Bun  
    (6, 7), -- Banh Mi - Baguette
    (7, 8), -- Ramen - Ramen Noodles
    (8, 3), -- Kimchi Fried Rice - Fish
    (8, 9), -- Kimchi Fried Rice - Kimchi
    (8, 11), -- Kimchi Fried Rice - Rice  
    (9, 6), -- Hot and Sour Soup - Pork
    (9, 8), -- Hot and Sour Soup - Ramen Noodles
    (10, 10), -- Cheesesteak Roll - Cheese
    (10, 1), -- Cheesesteak Roll - Beef
    (10, 7); -- Cheesesteak Roll - Baguette