<?php
use Livewire\Component;
use App\Models\MemoryLog;
use Livewire\Attributes\Polling;

new #[Polling(3000)] class extends Component { // auto refresh tiap 3 detik
    public float $currentRam = 0;
    public string $lastUpdated = "";

    public function mount(): void
    {
        $this->loadData();
    }

    public function loadData(): void
    {
        $log = MemoryLog::latest()->first();

        if ($log) {
            $this->currentRam = $log->ram_usage_percent;
            $this->lastUpdated = $log->created_at->diffForHumans();
        }
    }
};
?>

<div>
    <div class="flex items-center justify-center">
        <div class="text-2xl font-bold text-gray-800">{{ number_format($currentRam, 1) }}%</div>
    </div>
    <div class="flex items-center justify-center">
        <div class="text-lg font-bold text-gray-600">RAM Usage</div>
    </div>
    <div class="flex items-center justify-center">
        <div class="text-sm font-bold text-gray-400">
            Last Updated: {{ $lastUpdated ?: 'No data yet' }}
        </div>
    </div>
</div>
