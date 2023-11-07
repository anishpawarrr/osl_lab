create_db(){
    if [ -f "stud.db" ]; then
        echo "db exists"
    else
        touch stud.db
        echo "DB created"
    fi
}

insert_db(){
    echo "Enter name"
    read name
    echo "Enter no."
    read no

    echo "$name | $no" | cat >> stud.db
}

search_db(){
    echo "Enter no."
    read no

    grep $no stud.db | cat > search.db
    cat search.db
}

modify_db(){
    echo "enter no."
    read no
    grep -i -v $no stud.db | cat > temp.db
    mv temp.db stud.db
    insert_db
}


modify_db
# create_db
# insert_db
# search_db