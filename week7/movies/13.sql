select name from people
inner join
(select person_id from stars
inner join
(select id from movies
inner join (select movie_id from stars
where person_id =
(select people.id from people
where name = 'Kevin Bacon' and birth = 1958))
on id = movie_id)
on movie_id = id)
on people.id = person_id
where name != 'Kevin Bacon'