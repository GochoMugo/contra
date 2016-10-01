{
    "targets": [
        {
            "target_name": "path",
            "sources": [
                "path.cc"
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}