<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class MemoryLog extends Model
{
    protected $fillable = ["ram_usage_percent"];

    protected $casts = [
        "created_at" => "datetime",
        "updated_at" => "datetime",
        "ram_usage_percent" => "float",
    ];
}
