let rec prime n i = (
  if (i == 1) then 
    1 
  else
    if n mod i == 0 then 
      1 + prime n i-1
    else
      0 + prime n i-1 
)