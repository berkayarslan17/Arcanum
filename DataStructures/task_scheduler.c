#include <stdio.h>
#include <stdbool.h>

#define TASK_COUNT 5

typedef void (*callback_t)(void);

typedef struct {
    callback_t cb;
    unsigned int period_ms;
    unsigned int last_run_ms;
    bool is_enabled;
} task_t;

static task_t tasks[TASK_COUNT];

// SysTick değişkeni volatile olmalı
static volatile unsigned int g_system_ticks_ms = 0;

// SysTick Kesme Servis Rutini (ISR) - 1ms'de bir çağrılır
void systick_timer(void)
{
    g_system_ticks_ms++;
}

// Anlık zamanı güvenli okumak için yardımcı fonksiyon
static unsigned int get_system_ticks(void)
{
    // 32-bit okuma atomik kabul edilse de kesme anında tutarsızlığı önler
    return g_system_ticks_ms; 
}

void task_scheduler(void)
{
    unsigned int current_time = get_system_ticks();

    for (int i = 0; i < TASK_COUNT; i++)
    {
        if (!tasks[i].is_enabled || tasks[i].cb == NULL)
        {
            continue;
        }

        // Unsigned çıkarma işlemi (current_time - last_run_ms) 
        // integer overflow (taşma) durumunda dahi doğru farkı verir!
        if ((current_time - tasks[i].last_run_ms) >= tasks[i].period_ms)
        {
            // Zaman damgasını güncelle
            // 'last_run_ms = current_time' yerine '+=' kullanmak zaman kaymasını (drift) önler.
            tasks[i].last_run_ms += tasks[i].period_ms; 
            
            // Task callback fonksiyonunu çalıştır
            tasks[i].cb();
        }
    }
}

void task_1s_callback(void)
{
    printf("1000 ms task executed at %u ms\n", get_system_ticks());
}

void task_5ms_callback(void)
{
    // Note: Printf 1ms kesme yapısında main loop'u yavaşlatabilir
    // Gerçek sistemde burada pin toggle / sensör okuma yapılır.
}

void task_init(void)
{
    // Task 0: 5ms period
    tasks[0].cb = task_5ms_callback;
    tasks[0].period_ms = 5;
    tasks[0].last_run_ms = 0;
    tasks[0].is_enabled = true;

    // Task 1: 1000ms period
    tasks[1].cb = task_1s_callback;
    tasks[1].period_ms = 1000;
    tasks[1].last_run_ms = 0;
    tasks[1].is_enabled = true;
    
    // Diğer task'lar opsiyonel olarak initialize edilebilir
    for(int i = 2; i < TASK_COUNT; i++)
    {
        tasks[i].cb = NULL;
        tasks[i].is_enabled = false;
    }
}

int main(void)
{
    task_init();

    while (1)
    {
        task_scheduler();
    }

    return 0;
}